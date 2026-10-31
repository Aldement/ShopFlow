#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

/* Lit une ligne de texte (les espaces sont acceptes) */
void lireTexte(char dest[], int taille){
    fgets(dest, taille, stdin);
    dest[strcspn(dest, "\n")] = '\0';   /* on enleve le \n */
}

/* Demande un entier entre min et max, recommence si ce n'est pas bon */
int lireEntier(int min, int max){
    char ligne[50];
    int n;

    while (1){
        fgets(ligne, sizeof(ligne), stdin);

        if (sscanf(ligne, "%d", &n) != 1)
            printf("Ce n'est pas un nombre. Recommencez : ");
        else if (n < min || n > max)
            printf("Valeur entre %d et %d! : ", min, max);
        else
            return n;
    }
}

/* Demande un nombre decimal superieur ou egal a min */
double lireDouble(double min)
{
    char ligne[50];
    double x;

    while (1)
    {
        fgets(ligne, sizeof(ligne), stdin);

        if (sscanf(ligne, "%lf", &x) != 1)
            printf("Ce n'est pas un nombre. Recommencez : ");
        else if (x < min)
            printf("Valeur trop petite. Recommencez : ");
        else
            return x;
    }
}