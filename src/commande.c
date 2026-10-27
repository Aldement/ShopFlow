//
// Created by aldem on 26.10.2026.
//

#include "../include/commande.h"
#include "../include/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void creerCommande(Commande *tab) {
    int client;
    int nb_produits;

    printf("Saisir l'identifiand du client: ");
    scanf("%d", &client);
    tab.idClient = client;

    printf("Saisir le nombre de produits a commander: ");
    scanf("%d", &nb_produits);
    tab->lignes = malloc(nb_produits * sizeof(*tab->lignes));
    for (int i = 0; i < nb_produits; i++) {
        printf("Saisir la reference de produit: ");
        fgets(tab->lignes[i].refProduit, sizeof(tab->lignes[i].refProduit), stdin);
        tab->lignes[i].refProduit[strcspn(tab->lignes[i].refProduit, "\n")] = '\0';
        printf("Saisir le quantite de produit: ");
        scanf("%d", &tab->lignes[i].quantite);
    }
}
