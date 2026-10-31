#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "../include/initialisation.h"
#include "../include/clients.h"


/* initialisation.c : jeu de donnees de demonstration */

static Produit produitsInit[8] = {
    {"PRD-0001", "Clavier mecanique",  "Informatique",  79.90,  42, 10, 1},
    {"PRD-0002", "Souris sans fil",    "Informatique",  24.50,   8, 15, 1},
    {"PRD-0003", "Ecran 27 pouces",    "Informatique", 199.00,   6,  5, 1},
    {"PRD-0004", "Casque audio",       "Audio",         89.90,  25, 10, 1},
    {"PRD-0005", "Enceinte Bluetooth", "Audio",         59.90,  12,  8, 1},
    {"PRD-0006", "Cable HDMI 2 m",     "Accessoires",    9.90, 120, 30, 1},
    {"PRD-0007", "Hub USB-C 7 ports",  "Accessoires",   49.90,   4, 10, 1},
    {"PRD-0008", "Disque SSD 1 To",    "Stockage",     109.00,  18,  6, 1}
};

static Commande commandesInit[6] = {
    {1001, 1, {12, 3, 2026}, "LIVREE", 3, 3,
        (Ligne_Commande[]){
            {"PRD-0001", "Clavier mecanique", 2, 79.90, 159.80},
            {"PRD-0006", "Cable HDMI 2 m",    3,  9.90,  29.70},
            {"PRD-0004", "Casque audio",      1, 89.90,  89.90}},
        279.40, 5, 13.97, 265.43, 53.086, 318.516, 0.0,
        {"12 rue de la Paix", "Paris", "75002", "France"}},

    {1002, 2, {20, 4, 2026}, "LIVREE", 3, 3,
        (Ligne_Commande[]){
            {"PRD-0003", "Ecran 27 pouces", 2, 199.00, 398.00},
            {"PRD-0008", "Disque SSD 1 To", 2, 109.00, 218.00},
            {"PRD-0002", "Souris sans fil",  1,  24.50,  24.50}},
        640.50, 15, 96.075, 544.425, 108.885, 653.31, 0.0,
        {"5 avenue Foch", "Lyon", "69006", "France"}},

    {1003, 3, {5, 6, 2026}, "EXPEDIEE", 1, 1,
        (Ligne_Commande[]){
            {"PRD-0005", "Enceinte Bluetooth", 1, 59.90, 59.90}},
        59.90, 0, 0.0, 59.90, 11.98, 77.78, 5.90,
        {"27 cours Victor Hugo", "Bordeaux", "33000", "France"}},

    {1004, 1, {18, 9, 2026}, "EN_COURS", 2, 2,
        (Ligne_Commande[]){
            {"PRD-0008", "Disque SSD 1 To", 1, 109.00, 109.00},
            {"PRD-0002", "Souris sans fil",  2,  24.50,  49.00}},
        158.00, 5, 7.90, 150.10, 30.02, 180.12, 0.0,
        {"12 rue de la Paix", "Paris", "75002", "France"}},

    {1005, 4, {2, 10, 2026}, "ANNULEE", 1, 1,
        (Ligne_Commande[]){
            {"PRD-0004", "Casque audio", 2, 89.90, 179.80}},
        179.80, 5, 8.99, 170.81, 34.162, 204.972, 0.0,
        {"8 place du Capitole", "Toulouse", "31000", "France"}},

    {1006, 5, {25, 10, 2026}, "EN_COURS", 3, 3,
        (Ligne_Commande[]){
            {"PRD-0001", "Clavier mecanique", 1, 79.90, 79.90},
            {"PRD-0007", "Hub USB-C 7 ports", 1, 49.90, 49.90},
            {"PRD-0006", "Cable HDMI 2 m",    5,  9.90, 49.50}},
        179.30, 5, 8.965, 170.335, 34.067, 204.402, 0.0,
        {"3 rue de la Republique", "Marseille", "13001", "France"}}
};

static Client clientsInit[5] = {
    {1, "Bernard", "Julie", "j.bernard@mail.fr", "0612345678",
        {"12 rue de la Paix",      "Paris",     "75002", "France"}, 49, 0, 0, NULL, 1},
    {2, "Martin",  "Lucas", "l.martin@mail.fr",  "0623456789",
        {"5 avenue Foch",          "Lyon",      "69006", "France"}, 65, 0, 0, NULL, 1},
    {3, "Dubois",  "Emma",  "e.dubois@mail.fr",  "0634567890",
        {"27 cours Victor Hugo",   "Bordeaux",  "33000", "France"},  7, 0, 0, NULL, 1},
    {4, "Moreau",  "Hugo",  "h.moreau@mail.fr",  "0645678901",
        {"8 place du Capitole",    "Toulouse",  "31000", "France"},  0, 0, 0, NULL, 1},
    {5, "Petit",   "Lea",   "l.petit@mail.fr",   "0656789012",
        {"3 rue de la Republique", "Marseille", "13001", "France"}, 20, 0, 0, NULL, 1}
};

void initialiserDonneesTest(Boutique *b){
    strcpy(b->nom, "ShopFlow");

    /* 1. Produits : on reserve 10 places et on copie les 8 produits */
    b->capaciteProduits = 10;
    b->produits = malloc(b->capaciteProduits * sizeof(Produit));
    if (b->produits == NULL){
        printf("Erreur memoire.\n");
        exit(1);
    }
    for (int i = 0; i < 8; i++) b->produits[i] = produitsInit[i];

    b->nbProduits = 8;

    /* 2. Clients : on reserve 8 places et on copie les 5 clients */
    b->capaciteClients = 8;
    b->clients = malloc(b->capaciteClients * sizeof(Client));
    if (b->clients == NULL){
        printf("Erreur memoire.\n");
        exit(1);
    }
    for (int i = 0; i < 5; i++) b->clients[i] = clientsInit[i];

    b->nbClients = 5;

    /* 3. Commandes : chacune va dans le tableau de son client */
    for (int i = 0; i < 6; i++){
        int pos = rechercheClient(b, commandesInit[i].idClient);
        Client *cl = &b->clients[pos];

        /* si le tableau de commandes du client est plein, on le double */
        if (cl->nbCommandes == cl->capaciteCommandes){
            int nouvelle;
            if (cl->capaciteCommandes == 0) nouvelle = 2;
            else nouvelle = cl->capaciteCommandes * 2;

            Commande *tmp = realloc(cl->commandes, nouvelle * sizeof(Commande));
            if (tmp == NULL){
                printf("Erreur memoire.\n");
                exit(1);
            }
            cl->commandes = tmp;
            cl->capaciteCommandes = nouvelle;
        }

        Commande c = commandesInit[i];

        /* on copie les lignes dans un tableau alloue avec malloc */
        c.lignes = malloc(c.capaciteLignes * sizeof(Ligne_Commande));
        if (c.lignes == NULL){
            printf("Erreur memoire.\n");
            exit(1);
        }
        for (int j = 0; j < c.nbLignes; j++) c.lignes[j] = commandesInit[i].lignes[j];

        cl->commandes[cl->nbCommandes] = c;
        cl->nbCommandes++;
    }

    b->numeroSuivant = 1007;
    b->idClientSuivant = 6;
}

/* Libere TOUTE la memoire, du plus profond au plus haut */
void detruireBoutique(Boutique *b){
    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++) free(b->clients[i].commandes[j].lignes);   /* lignes de chaque commande */

        free(b->clients[i].commandes);/* commandes de chaque client */
    }
    free(b->clients);
    free(b->produits);
}