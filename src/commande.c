#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/commande.h"
#include "../include/produits.h"
#include "../include/clients.h"
#include "../include/utils.h"

/* Calcule tous les montants d'une commande */
void calculerMontants(Commande *c){
    double brut = 0;

    for (int i = 0; i < c->nbLignes; i++) brut = brut + c->lignes[i].sousTotalHT;

    c->montantBrutHT = brut;

    /* palier de remise, calcule sur le brut */
    if (brut < 100) c->tauxRemise = 0;
    else if (brut < 300) c->tauxRemise = 5;
    else if (brut < 600) c->tauxRemise = 10;
    else  c->tauxRemise = 15;

    c->montantRemise = brut * c->tauxRemise / 100;
    c->montantHT = brut - c->montantRemise;
    c->montantTVA = c->montantHT * 0.20;

    /* frais de port : offerts a partir de 60 EUR de HT brut */
    if (brut >= 60) c->fraisPort = 0;
    else c->fraisPort = 5.90;

    c->montantTTC = c->montantHT + c->montantTVA + c->fraisPort;
}

/* Cherche une commande par son numero dans tous les clients.
   Renvoie 1 si trouvee (et remplit iClient et iCommande), sinon 0. */
int trouverCommande(Boutique *b, int num, int *iClient, int *iCommande){
    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            if (b->clients[i].commandes[j].numero == num){
                *iClient = i;
                *iCommande = j;
                return 1;
            }
        }
    }
    return 0;
}

/* Ajoute UNE ligne a la commande. Renvoie 1 si OK, 0 si erreur. */
int saisirLigne(Boutique *b, Commande *cmd){
    char ref[12];

    printf("Reference du produit : ");
    lireTexte(ref, 12);

    int p = rechercheProduit(b, ref);
    if (p == -1){
        printf("Produit introuvable.\n");
        return 0;
    }
    if (b->produits[p].actif == 0) {
        printf("Produit inactif.\n");
        return 0;
    }

    /* pas deux lignes pour le meme produit */
    for (int i = 0; i < cmd->nbLignes; i++){
        if (strcmp(cmd->lignes[i].refProduit, ref) == 0){
            printf("Ce produit est deja dans la commande.\n");
            return 0;
        }
    }

    if (b->produits[p].quantiteStock == 0){
        printf("Il n'y a plus de produit disponibles.\n");
        return 0;
    }

    printf("Quantite (stock disponible : %d) : ", b->produits[p].quantiteStock);
    int q = lireEntier(1, b->produits[p].quantiteStock);

    /* si le tableau de lignes est plein, on le double */
    if (cmd->nbLignes == cmd->capaciteLignes){
        int nouvelle = cmd->capaciteLignes * 2;
        Ligne_Commande *tmp = realloc(cmd->lignes, nouvelle * sizeof(Ligne_Commande));
        if (tmp == NULL){
            printf("Erreur memoire.\n");
            return 0;
        }
        cmd->lignes = tmp;
        cmd->capaciteLignes = nouvelle;
    }

    int n = cmd->nbLignes;
    strcpy(cmd->lignes[n].refProduit, b->produits[p].reference);
    strcpy(cmd->lignes[n].designation, b->produits[p].designation);
    cmd->lignes[n].quantite = q;
    cmd->lignes[n].prixUnitaire = b->produits[p].prixUnitaireHT;
    cmd->lignes[n].sousTotalHT = q * b->produits[p].prixUnitaireHT;
    cmd->lignes[n].quantiteRetournee = 0;
    cmd->nbLignes++;

    b->produits[p].quantiteStock = b->produits[p].quantiteStock - q;

    return 1;
}

void creerCommande(Boutique *b){
    printf("ID du client : ");
    int id = lireEntier(1, 1000000);

    int pos = rechercheClient(b, id);
    if (pos == -1 || b->clients[pos].actif == 0){
        printf("Client introuvable.\n");
        return;
    }

    Client *cl = &b->clients[pos];

    /* si le tableau de commandes du client est plein, on le double */
    if (cl->nbCommandes == cl->capaciteCommandes){
        int nouvelle;
        if (cl->capaciteCommandes == 0)
            nouvelle = 2;
        else
            nouvelle = cl->capaciteCommandes * 2;

        Commande *tmp = realloc(cl->commandes, nouvelle * sizeof(Commande));
        if (tmp == NULL){
            printf("Erreur memoire.\n");
            return;
        }
        cl->commandes = tmp;
        cl->capaciteCommandes = nouvelle;
    }

    Commande cmd;
    cmd.numero = b->numeroSuivant;   /* numero donne par la boutique */
    cmd.idClient = id;

    printf("Jour : ");
    cmd.dateCommande.jour = lireEntier(1, 31);
    printf("Mois : ");
    cmd.dateCommande.mois = lireEntier(1, 12);
    printf("Annee : ");
    cmd.dateCommande.annee = lireEntier(2000, 2100);

    strcpy(cmd.statut, "EN_COURS");
    cmd.adresseLivraisn = cl->adresse;   /* on copie l'adresse du client */

    cmd.nbLignes = 0;
    cmd.capaciteLignes = 4;
    cmd.lignes = malloc(cmd.capaciteLignes * sizeof(Ligne_Commande));
    if (cmd.lignes == NULL){
        printf("Erreur memoire.\n");
        return;
    }

    printf("Combien de produits differents : ");
    int nb = lireEntier(1, 50);

    int fait = 0;
    while (fait < nb){
        if (saisirLigne(b, &cmd) == 1){
            fait++;
        }
        else{
            printf("Reessayer ? (1 = oui, 0 = abandonner) : ");
            if (lireEntier(0, 1) == 0)
                break;
        }
    }

    if (cmd.nbLignes == 0){
        free(cmd.lignes);
        printf("Commande abandonnee.\n");
        return;
    }

    calculerMontants(&cmd);

    cl->commandes[cl->nbCommandes] = cmd;
    cl->nbCommandes++;
    b->numeroSuivant++;

    /* 1 point de fidelite par tranche de 10 EUR TTC */
    cl->pointsFidelite = cl->pointsFidelite + (int)(cmd.montantTTC / 10);

    printf("Commande %d creee. Total TTC : %.2f EUR\n", cmd.numero, cmd.montantTTC);
}

void afficherUneCommande(Boutique *b){
    int ic, jc;

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &ic, &jc) == 0){
        printf("Commande introuvable.\n");
        return;
    }

    Commande *c = &b->clients[ic].commandes[jc];

    printf("\n===== COMMANDE %d =====\n", c->numero);
    printf("Client : %d\n", c->idClient);
    printf("Date : %02d/%02d/%d\n", c->dateCommande.jour, c->dateCommande.mois, c->dateCommande.annee);
    printf("Statut : %s\n", c->statut);

    printf("\nLignes :\n");
    for (int i = 0; i < c->nbLignes; i++){
        printf("  %s - %s : %d x %.2f = %.2f EUR\n",
               c->lignes[i].refProduit, c->lignes[i].designation,
               c->lignes[i].quantite, c->lignes[i].prixUnitaire,
               c->lignes[i].sousTotalHT);
    }

    printf("\nTotal HT brut : %.2f EUR\n", c->montantBrutHT);
    printf("Remise (%.0f%%) : -%.2f EUR\n", c->tauxRemise, c->montantRemise);
    printf("Total HT : %.2f EUR\n", c->montantHT);
    printf("TVA 20%% : %.2f EUR\n", c->montantTVA);
    printf("Frais de port : %.2f EUR\n", c->fraisPort);
    printf("TOTAL TTC : %.2f EUR\n", c->montantTTC);
    printf("Livraison : %s, %s %s, %s\n", c->adresseLivraisn.rue,
           c->adresseLivraisn.codePostal, c->adresseLivraisn.ville,
           c->adresseLivraisn.pays);
}

void changerStatut(Boutique *b){
    int ic, jc;

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &ic, &jc) == 0){
        printf("Commande introuvable.\n");
        return;
    }

    Commande *c = &b->clients[ic].commandes[jc];

    if (strcmp(c->statut, "EN_COURS") == 0){
        strcpy(c->statut, "EXPEDIEE");
        printf("La commande est maintenant EXPEDIEE.\n");
    }
    else if (strcmp(c->statut, "EXPEDIEE") == 0){
        strcpy(c->statut, "LIVREE");
        printf("La commande est maintenant LIVREE.\n");
    }
    else{
        printf("Impossible de changer le statut (%s).\n", c->statut);
    }
}

void annulerCommande(Boutique *b){
    int ic, jc;

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &ic, &jc) == 0){
        printf("Commande introuvable.\n");
        return;
    }

    Commande *c = &b->clients[ic].commandes[jc];

    /* annulation possible seulement si EN_COURS */
    if (strcmp(c->statut, "EN_COURS") != 0){
        printf("On ne peut annuler qu'une commande EN_COURS.\n");
        return;
    }

    /* on remet les quantites dans le stock */
    for (int i = 0; i < c->nbLignes; i++){
        int p = rechercheProduit(b, c->lignes[i].refProduit);
        if (p != -1) b->produits[p].quantiteStock = b->produits[p].quantiteStock + c->lignes[i].quantite;
    }

    /* on retire les points de fidelite */
    b->clients[ic].pointsFidelite = b->clients[ic].pointsFidelite - (int)(c->montantTTC / 10);
    if (b->clients[ic].pointsFidelite < 0) b->clients[ic].pointsFidelite = 0;

    strcpy(c->statut, "ANNULEE");
    printf("Commande annulee.\n");
}

void ajouterLigne(Boutique *b){
    int ic, jc;

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &ic, &jc) == 0){
        printf("Commande introuvable.\n");
        return;
    }

    Commande *c = &b->clients[ic].commandes[jc];

    if (strcmp(c->statut, "EN_COURS") != 0){
        printf("Ajout possible seulement si la commande est EN_COURS.\n");
        return;
    }

    if (saisirLigne(b, c) == 1){
        calculerMontants(c);
        printf("Ligne ajoutee. Nouveau total TTC : %.2f EUR\n", c->montantTTC);
    }
}

void supprimerLigne(Boutique *b){
    int ic, jc;
    char ref[12];

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &ic, &jc) == 0){
        printf("Commande introuvable.\n");
        return;
    }

    Commande *c = &b->clients[ic].commandes[jc];

    if (strcmp(c->statut, "EN_COURS") != 0){
        printf("Suppression possible seulement si la commande est EN_COURS.\n");
        return;
    }

    if (c->nbLignes == 1){
        printf("Derniere ligne : annulez plutot la commande.\n");
        return;
    }

    printf("Reference du produit a retirer : ");
    scanf("%11s", ref);

    /* on cherche la ligne */
    int pos = -1;
    for (int i = 0; i < c->nbLignes; i++){
        if (strcmp(c->lignes[i].refProduit, ref) == 0)
            pos = i;
    }

    if (pos == -1){
        printf("Ce produit n'est pas dans la commande.\n");
        return;
    }

    /* on remet la quantite dans le stock */
    int p = rechercheProduit(b, ref);
    if (p != -1) b->produits[p].quantiteStock = b->produits[p].quantiteStock + c->lignes[pos].quantite;

    /* on decale les lignes suivantes d'une case vers la gauche */
    for (int i = pos; i < c->nbLignes - 1; i++) c->lignes[i] = c->lignes[i + 1];

    c->nbLignes--;
    calculerMontants(c);
    printf("Ligne supprimee. Nouveau total TTC : %.2f EUR\n", c->montantTTC);
}