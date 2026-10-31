//
// Created by aldem on 31.10.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/produits.h"
#include "../include/utils.h"

/* Renvoie la position du produit dans le tableau, ou -1 s'il n'existe pas */
int rechercheProduit(Boutique *b, char ref[]){
    for (int i = 0; i < b->nbProduits; i++){
        if (strcmp(b->produits[i].reference, ref) == 0)
            return i;
    }
    return -1;
}

void ajouterProduit(Boutique *b){
    Produit p;
    char ref[12];
    int choix;

    printf("Reference (ex : PRD-0009) : ");
    lireTexte(ref, 12);

    /* la reference doit etre unique (meme pour les produits desactives) */
    if (rechercheProduit(b, ref) != -1){
        printf("Cette reference existe deja.\n");
        return;
    }

    /* si le tableau est plein, on le double*/
    if (b->nbProduits == b->capaciteProduits){
        int nouvelle = b->capaciteProduits * 2;
        if (nouvelle == 0)
            nouvelle = 10;

        Produit *tmp = realloc(b->produits, nouvelle * sizeof(Produit));
        if (tmp == NULL){
            printf("Erreur memoire.\n");
            return;
        }
        b->produits = tmp;
        b->capaciteProduits = nouvelle;
    }

    strcpy(p.reference, ref);

    printf("Designation : ");
    lireTexte(p.designation, 60);

    printf("Categorie : 1.Informatique -- 2.Audio -- 3.Accessoires -- 4.Stockage : ");
    choix = lireEntier(1, 4);
    if (choix == 1) strcpy(p.categorie, "Informatique");
    if (choix == 2) strcpy(p.categorie, "Audio");
    if (choix == 3) strcpy(p.categorie, "Accessoires");
    if (choix == 4) strcpy(p.categorie, "Stockage");

    printf("Prix unitaire HT : ");
    p.prixUnitaireHT = lireDouble(0.01);

    printf("Stock disponible : ");
    p.quantiteStock = lireEntier(0, 1000000);

    printf("Seuil d'alerte : ");
    p.seuilAlerte = lireEntier(0, 1000000);

    p.actif = 1;

    b->produits[b->nbProduits] = p;
    b->nbProduits++;

    printf("Produit ajoute.\n");
}

void modifierProduit(Boutique *b){
    char ref[12];
    int choix;

    printf("Reference du produit a modifier : ");
    lireTexte(ref, 12);

    int pos = rechercheProduit(b, ref);
    if (pos == -1){
        printf("Produit introuvable.\n");
        return;
    }

    printf("Que modifier ? 1.Prix -- 2.Stock -- 3.Seuil d'alerte : ");
    choix = lireEntier(1, 3);

    if (choix == 1){
        printf("Nouveau prix HT : ");
        b->produits[pos].prixUnitaireHT = lireDouble(0.01);
    }
    else if (choix == 2){
        printf("Nouveau stock : ");
        b->produits[pos].quantiteStock = lireEntier(0, 1000000);
    }
    else{
        printf("Nouveau seuil : ");
        b->produits[pos].seuilAlerte = lireEntier(0, 1000000);
    }

    printf("Produit modifie.\n");
}

void supprimerProduit(Boutique *b){
    char ref[12];

    printf("Reference du produit a supprimer : ");
    lireTexte(ref, 12);

    int pos = rechercheProduit(b, ref);
    if (pos == -1){
        printf("Produit introuvable.\n");
        return;
    }

    /* on regarde toutes les lignes de toutes les commandes de tous les clients */
    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            Commande *cmd = &b->clients[i].commandes[j];

            if (strcmp(cmd->statut, "ANNULEE") != 0){
                for (int k = 0; k < cmd->nbLignes; k++){
                    if (strcmp(cmd->lignes[k].refProduit, ref) == 0){
                        printf("Suppression refusee : produit utilise dans une commande.\n");
                        return;
                    }
                }
            }
            else {
                printf("Le produit est deja supprimee!");
                return;
            }
        }
    }

    b->produits[pos].actif = 0;
    printf("Produit desactive.\n");
}

void afficherCatalogue(Boutique *b){
    double valeur;
    double total = 0;

    printf("\n===== CATALOGUE =====\n");

    for (int i = 0; i < b->nbProduits; i++){
        if (b->produits[i].actif == 1){
            valeur = b->produits[i].quantiteStock * b->produits[i].prixUnitaireHT;
            total += valeur;

            printf("\n%s - %s (%s)", b->produits[i].reference,
                   b->produits[i].designation, b->produits[i].categorie);
            printf("\n  Prix HT : %.2f  Stock : %d  Seuil : %d",
                   b->produits[i].prixUnitaireHT,
                   b->produits[i].quantiteStock,
                   b->produits[i].seuilAlerte);
            printf("\n  Valeur du stock : %.2f EUR\n", valeur);
        }
    }

    printf("\nValeur totale du stock : %.2f EUR\n", total);
}

void rechercherProduit(Boutique *b){
    int choix;
    char texte[60];

    printf("Rechercher par : 1.Reference exacte -- 2.Mot-cle de la designation : ");
    choix = lireEntier(1, 2);

    printf("Texte a chercher : ");
    lireTexte(texte, 60);

    int trouve = 0;

    for (int i = 0; i < b->nbProduits; i++)
    {
        int ok = 0;

        if (choix == 1 && strcmp(b->produits[i].reference, texte) == 0)
            ok = 1;

        /* strstr cherche un morceau de texte dans un autre texte */
        else if (choix == 2 && strstr(b->produits[i].designation, texte) != NULL)
            ok = 1;

        if (ok == 1 && b->produits[i].actif == 1)
        {
            printf("%s - %s - %.2f EUR - stock %d\n",
                   b->produits[i].reference, b->produits[i].designation,
                   b->produits[i].prixUnitaireHT, b->produits[i].quantiteStock);
            trouve = 1;
        }
    }

    if (trouve == 0) printf("Aucun produit trouve.\n");
}