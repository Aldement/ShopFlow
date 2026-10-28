#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

void initialiserDonneesTest(Boutique *b) {
    /* 1. Catalogue : allocation dynamique de 10 emplacements */
    b->capaciteProduits = 10;
    b->produits = (Produit *)malloc(b->capaciteProduits * sizeof(Produit));
    if (b->produits == NULL) { /* ... gestion d'erreur ... */ }
    b->nbProduits = 0;
    Produit modele[] = {
        {"PRD-0001", "Clavier mecanique",  "Informatique",  79.90,  42, 10, 1},
        {"PRD-0002", "Souris sans fil",    "Informatique",  24.50,   8, 15, 1},
        {"PRD-0003", "Ecran 27 pouces",    "Informatique", 199.00,   6,  5, 1},
        {"PRD-0004", "Casque audio",       "Audio",         89.90,  25, 10, 1},
        {"PRD-0005", "Enceinte Bluetooth", "Audio",         59.90,  12,  8, 1},
        {"PRD-0006", "Cable HDMI 2 m",     "Accessoires",    9.90, 120, 30, 1},
        {"PRD-0007", "Hub USB-C 7 ports",  "Accessoires",   49.90,   4, 10, 1},
        {"PRD-0008", "Disque SSD 1 To",    "Stockage",     109.00,  18,  6, 1}
    };
    for (int i = 0; i < 8; i++)
        b->produits[b->nbProduits++] = modele[i];

    /* 2. Clients : allocation dynamique de 8 emplacements */
    b->capaciteClients = 8;
    b->clients = (Client *)malloc(b->capaciteClients * sizeof(Client));
    if (b->clients == NULL) { /* ... gestion d'erreur ... */ }
    b->nbClients = 0;
    /* ... 5 clients, chacun avec commandes = NULL et capaciteCommandes = 0 ... */

    /* 3. Commande n01 : 3 lignes allouees dynamiquement */
    Commande c1;
    c1.numero       = 1001;
    c1.idClient     = 1;
    c1.dateCommande = (Date){12, 3, 2026};
    strcpy(c1.statut, "LIVREE");
    c1.capaciteLignes = 3;
    c1.lignes = (LigneCommande *)malloc(c1.capaciteLignes * sizeof(LigneCommande));
    c1.nbLignes = 0;
    /* ... ajout des lignes, puis calculCommande(&c1) et rattachement au client ... */
}
/* Liberation complete : une seule fuite memoire est sanctionnee */
void detruireBoutique(Boutique *b) {
    for (int i = 0; i < b->nbC lients; i++) {
        for (int j = 0; j < b->clients[i].nbCommandes; j++)
            free(b->clients[i].commandes[j].lignes);
        free(b->clients[i].commandes);
    }
    free(b->clients);
    free(b->produits);
}