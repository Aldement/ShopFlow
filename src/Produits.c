//
// Created by gaelt on 26.10.26.
//

#include "../include/Produits.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



static Produit *modele = NULL;
int taille = 0;

static void saisirProduit(Produit *modele) {
    int p;
    char designation[20];
    printf("Saisir le designation de votre produit\n");
    fgets(designation,sizeof(designation), stdin);
    strcpy(modele[taille].designation, designation);
    printf("Dans quelle categorie vouliez vous mettre le produit ?\n");
    scanf("%d", &p);
    switch (p) {
        case 1: strcpy(modele[taille].categorie, "Informatique"); break;
        case 2: strcpy(modele[taille].categorie,"Audio"); break;
        case 3: strcpy(modele[taille].categorie,"Accesoires"); break;
        case 4: strcpy(modele[taille].categorie, "Stockage"); break;
        default: printf("Choix invalide.\n"); break;
    }
    printf("Saisir le prix de produit: \n");
    scanf("%lf", &modele[taille].prixUnitaireHT);
    printf("Saisir le stock disponible de produit");
    scanf("%d", &modele[taille].quantiteStock);
    printf("Saisir le seuil de reaprovisionnement");
    scanf("%d", &modele[taille].seuilAlerte);
}

static void ajouterProduit(void) {
    Produit *modele_tmp = realloc(modele, (taille+1) * sizeof(Produit));
    modele = modele_tmp;
    char categorie[30];
    snprintf(modele[taille].reference, sizeof(modele[taille].reference), "PRD-%04d", taille);
    saisirProduit(modele);
    modele[taille].actif = 1;
    printf("Produit crée avec succès");
}

static void mettreAJourProduit(void) {
    char refProduit[12];
    printf("Saisir la reference de produit a modifier: ");
    fgets(refProduit, sizeof(refProduit), stdin);
    refProduit[strcspn(refProduit, "\n")] = '\0';
    int mod = -1;
    for (int i = 0; i < taille; i++) {
        if (strcmp(modele[i].reference, refProduit) == 0) {
            mod = i;
            break;
        }
    }
    if (mod != -1) {
        int nb_mod;
        printf("Les attributs possibles a changer: designation, categorie, prixUnitaireHT, quantiteStock, seuilAlerte.");
        do {
            printf("Saisir le nombre des attributs a modifier (5 max): ");
            scanf("%d" ,&nb_mod);
        } while (nb_mod < 1 || nb_mod > 5);
        char att[15];
        if (nb_mod == 5) {
            saisirProduit(modele);
        }
        else {
            for (int i = 0; i < nb_mod; i++) {
                printf("Saisir l'attribut a modifier: ");
                fgets(att, sizeof(att), stdin);
                att[strcspn(att, "\n")] = '\0';
                char attModifiee[60];
                int nbModifiee;
                printf("Saisir la valeur modifiee: ");
                if (strcmp(att, "designation") == 0) {
                    fgets(attModifiee, sizeof(attModifiee), stdin);
                    attModifiee[strcspn(attModifiee, "\n")] = '\0';
                    strcpy(modele[mod].designation, attModifiee);
                }
                else if (strcmp(att, "categorie") == 0) {
                    fgets(attModifiee, sizeof(attModifiee), stdin);
                    attModifiee[strcspn(attModifiee, "\n")] = '\0';
                    strcpy(modele[mod].categorie, attModifiee);
                }
                else if (strcmp(att, "prixUnitaireHT") == 0) {
                    double nouveauPrix;
                    if (scanf("%lf", &nouveauPrix) == 1)
                        modele[mod].prixUnitaireHT = nouveauPrix;
                }
                else if (strcmp(att, "quantiteStock") == 0) {
                    scanf("%d", &nbModifiee);
                    modele[mod].quantiteStock = nbModifiee;
                }
                else if (strcmp(att, "seuilAlerte") == 0) {
                    scanf("%d", &nbModifiee);
                    modele[mod].seuilAlerte = nbModifiee;
                }
                else
                    printf("Attribut inconnu : %s\n", att);
            }
        }
    }
    else {
        printf("Le produit de reference %s n'existe pas!", refProduit);
    }
}