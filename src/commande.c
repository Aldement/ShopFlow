//
// Created by aldem on 26.10.2026.
//

#include "../include/commande.h"
#include "../include/types.h"
#include "../include/produits.h"
#include "../include/Clients.h"
#include "../include/Initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Produit *modele = NULL;
static Commande *commande = NULL;
int tailleCommande = 0;
int tailleModele;

static void saisirLigne(int t, int i) {
    printf("Saisir la reference de produit: ");
    fgets(commande[t].lignes[i].refProduit, sizeof(commande[t].lignes[i].refProduit), stdin);
    commande[t].lignes[i].refProduit[strcspn(commande[t].lignes[i].refProduit, "\n")] = '\0';
    int j;
    int found = 0;
    for (j = 0; j < tailleModele; j++) {
        if (strcmp(commande[t].lignes[i].refProduit, modele[j].reference) == 0) {
            strcpy(commande[t].lignes[i].designation, modele[j].designation);
            commande[t].lignes[i].prixUnitaire = modele[j].prixUnitaireHT;
            found = 1;
            break;
        }
    }
    if (found == 0) printf("Le produit de cette reference n'existe pas");

    do {
        printf("Saisir le quantite de produit: ");
        scanf("%d", &commande[t].lignes[i].quantite);
        if (commande[t].lignes[i].quantite > modele[j].quantiteStock) {
            printf("Il n'y a pas assez de ces produits pour votre commande, saisissez le quantite plus petite.\n");
        }
    } while (commande[t].lignes[i].quantite > modele[j].quantiteStock);
    commande[t].lignes[i].sousTotalHT = commande[t].lignes[i].quantite * commande[t].lignes[i].prixUnitaire;
    commande[t].montantBrutHT += commande[t].lignes[i].sousTotalHT;
}

static void changementMontant(int i) {
    int tauxRemise;
    if (commande[i].montantBrutHT < 100)
        tauxRemise = 0;
    else if (commande[i].montantBrutHT < 299.99)
        tauxRemise = 5;
    else if (commande[i].montantBrutHT < 599.99)
        tauxRemise = 10;
    else tauxRemise = 20;
    commande[i].montantRemise = commande[i].montantBrutHT * tauxRemise / 100;
    commande[i].montantHT = commande[i].montantBrutHT - commande[i].montantRemise;
    commande[i].montantTVA = 0.2 * commande[i].montantHT;
    if (commande[i].montantBrutHT >= 60)
        commande[i].fraisPort = 5.9;
    else commande[i].fraisPort = 0;
    commande[i].montantTTC = commande[i].montantHT + commande[i].montantTVA + commande[i].fraisPort;
}

static void creerCommande(void) {
    int client;
    int nb_produits;
    Commande *commande_tmp = realloc(modele, (tailleCommande+1) * sizeof(Commande));
    commande = commande_tmp;
    commande[tailleCommande].numero = tailleCommande + 1;
    printf("Saisir l'identifiand du client: ");
    scanf("%d", &client);
    commande[tailleCommande].idClient = client;
    printf("Saisir la date de commande (Jour, Mois, Annee): ");
    scanf("%d, %d, %d", &commande[tailleCommande].dateCommande.jour, &commande[tailleCommande].dateCommande.mois, &commande[tailleCommande].dateCommande.annee);
    strcpy(commande[tailleCommande].statut, "EN_COURS");
    printf("Saisir le nombre de produits a commander: ");
    scanf("%d", &nb_produits);
    commande[tailleCommande].capaciteLignes = nb_produits + 1;
    commande[tailleCommande].lignes = malloc(nb_produits * sizeof(Ligne_Commande));
    for (int i = 0; i < nb_produits; i++) {
        saisirLigne(tailleCommande, i);
    }
    changementMontant(tailleCommande);
    printf("Saisir l'adresse de livraison (rue, ville, code postal, pays): ");
    fgets(commande[tailleCommande].adresseLivraisn.rue, 80, stdin);
    commande[tailleCommande].adresseLivraisn.rue[strcspn(commande[tailleCommande].adresseLivraisn.rue, "\n")] = '\0';
    fgets(commande[tailleCommande].adresseLivraisn.ville, 50, stdin);
    commande[tailleCommande].adresseLivraisn.ville[strcspn(commande[tailleCommande].adresseLivraisn.ville, "\n")] = '\0';
    scanf("%s", commande[tailleCommande].adresseLivraisn.codePostal);
    fgets(commande[tailleCommande].adresseLivraisn.pays, 50, stdin);
    commande[tailleCommande].adresseLivraisn.pays[strcspn(commande[tailleCommande].adresseLivraisn.pays, "\n")] = '\0';
    tailleCommande++;
}


static void ajouterLigne(void) {
    int num;
    printf("Saisir le numero de commande: ");
    scanf("%d", &num);
    if (num > tailleCommande) printf("La commande avec ce numero n'existe pas!");
    else {
        for (int i = 0; i < tailleCommande; i++) {
            if (commande[i].numero == num) {
                if (strcmp(commande[i].statut, "EN_COURS") == 0) {
                    commande[i].nbLignes++;
                    commande[i].capaciteLignes++;
                    commande[i].lignes = realloc(commande[i].lignes, commande[i].nbLignes * sizeof(Ligne_Commande));
                    saisirLigne(i, (commande[i].nbLignes) - 1);
                    changementMontant(i);
                    break;
                }
                else {
                    printf("Impossible d'ajouter une ligne si le statut de commande n'est pas en cours!");
                    break;
                }
            }
        }
    }
}

static void supprimerLigne(void) {
    int num;
    printf("Saisir le numero de commande: ");
    scanf("%d", &num);
    if (num > tailleCommande) printf("La commande avec ce numero n'existe pas!");
    else {
        for (int i = 0; i < tailleCommande; i++) {
            if (commande[i].numero == num) {
                if (strcmp(commande[i].statut, "EN_COURS") == 0) {
                    char reference[12];
                    printf("Saisir la reference de produit pour supprimer la ligne du commande: ");
                    fgets(reference, sizeof(reference), stdin);
                    reference[strcspn(reference, "\n")] = '\0';
                    for (int j = 0; j < commande[i].nbLignes - 1; j++) {
                        if (strcmp(commande[i].lignes[j].refProduit, reference) == 0) {
                            commande[i].montantBrutHT -= commande[i].lignes[j].sousTotalHT;
                            for (int k = j; k < commande[i].nbLignes - 1; k++) {
                                commande[i].lignes[k] = commande[i].lignes[k + 1];
                            }
                            break;
                        }
                    }
                    commande[i].nbLignes--;
                    commande[i].capaciteLignes--;
                    commande[i].lignes = realloc(commande[i].lignes, commande[i].nbLignes * sizeof(Ligne_Commande));
                    changementMontant(i);
                    break;
                }
                else {
                    printf("Impossible d'ajouter une ligne si le statut de commande n'est pas en cours!");
                    break;
                }
            }
        }
    }
}

static void changerStatut(void){}

static void annulerCommande(void){}

static void afficherCommande(void){}