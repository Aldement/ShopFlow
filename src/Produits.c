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

static void ajouterProduit(void) {
    Produit *modele_tmp = realloc(modele, (taille+1) * sizeof(Produit));
    modele = modele_tmp;
    char designation[20];
    char categorie[30];
    int p;
    snprintf(modele[taille].reference, sizeof(modele[taille].reference), "PRD-%04d", taille);
    printf("Saisir le nom de votre produit\n");
    fgets(designation,sizeof(designation), stdin);
    strcpy(modele[taille].designation, designation);
    printf("Dans quelle categorie vouliez vous mettre le produit ?\n");
    scanf("%d", &p);
    switch (p) {
        case 1: strcpy(categorie, "Informatique"); break;
        case 2: strcpy(categorie,"Audio"); break;
        case 3: strcpy(categorie,"Accesoires"); break;
        case 4: strcpy(categorie, "Stockage"); break;
        default: printf("Choix invalide.\n"); break;
    }
    printf("Saisir le prix de produit: \n");
    scanf("%x", &modele[taille].prixUnitaireHT);
    printf("Saisir le stock disponible de produit");
    scanf("%d", &modele[taille].quantiteStock);
    printf("Saisir le seuil de reaprovisionnement");
    scanf("%d", &modele[taille].seuilAlerte);
    modele[taille].actif = 1;
    printf("Produit crée avec succès");
}
