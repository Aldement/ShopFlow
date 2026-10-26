#include <stdio.h>
#include <string.h>


static void ajouterProduit(void) {
    char designation[20];
    int prix;
    char categorie[30];
    int p;
    printf("Ecrivez le nom de votre produit\n");
    fgets(designation,sizeof(designation), stdin);
    printf("Le prix de votre produit ?\n");
    scanf("%d", &prix);
    printf("Dans quelle categorie vouliez vous mettre le produit ?\n");
    scanf("%d", &p);
    switch (p) {
        case 1: strcpy(categorie, "Informatique"); break;
        case 2: strcpy(categorie,"Audio"); break;
        case 3: strcpy(categorie,"Accesoires"); break;
        case 4: strcpy(categorie, "Stockage"); break;
        default: printf("Choix invalide.\n"); break;
    }
    printf("Produit créer avec succès");
}

ajouterProduit();