//
// Created by aldem on 26.10.2026.
//

#include "../include/commande.h"
#include "../include/types.h"
#include <stdio.h>
#include <stdlib.h>


static void creerCommande(Commande *tab) {
    Commande command;
    int client;
    int nb_produits;

    printf("Saisir l'identifiand du client: ");
    scanf("%d", &client);

    printf("Saisir le nombre de produits a commander: ");
    scanf("%d", &nb_produits);
    tab->lignes = malloc(nb_produits * sizeof(tab));
    for (int i)
}
