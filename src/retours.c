//
// Created by aldem on 03.11.2026.
//

#include <stdio.h>
#include <string.h>
#include "../include/retours.h"
#include"../include/types.h"
#include "../include/produits.h"
#include"../include/clients.h"
#include "../include/commande.h"
#include"../include/utils.h"


/* Les regles de retours et des avoirs:
 * 1. On peut retourner un produit seulement si la commande est LIVREE
 * 2. On ne peut pas retourner plus qu'on a achete
 * 3. Avoir = quantite retourne * prixTVA
 */

void returnerProduit(Boutique *b) {
    int iClient, iCommande;
    char ref[12];

    printf("Numero de commande : ");
    int num = lireEntier(1, 1000000);

    if (trouverCommande(b, num, &iClient, &iCommande) == 0) {
        printf("Ce commande n'existe pas");
        return;
    }

    Commande *c = &b->clients[iClient].commandes[iCommande];

    /* On peut retourner un produit seulement si la commande est LIVREE */
    if (strcmp(c->statut, "LIVREE") != 0) {
        printf("Retour possible seulement pour une commande deja LIVREE.\n");
        return;
    }

    printf("Reference du produit a retourner : ");
    lireTexte(ref, 12);

    int pos = -1;
    for (int i = 0; i < c->nbLignes; i++)
    {
        if (strcmp(c->lignes[i].refProduit, ref) == 0)
            pos = i;
    }

    if (pos == -1)
    {
        printf("Ce produit n'est pas dans la commande.\n");
        return;
    }

    /* On ne peut pas retourner plus que ce qu'on a achete*/
    int reste = c->lignes[pos].quantite - c->lignes[pos].quantiteRetournee;

    if (reste == 0)
    {
        printf("Tous les produits de cette ligne ont deja ete retournes.\n");
        return;
    }

    printf("Quantite a retourner (maximum %d) : ", reste);
    int q = lireEntier(1, reste);

    /* Calcul de l'avoir */
    double montant = q * c->lignes[pos].prixUnitaire;
    montant = montant * (1 - c->tauxRemise / 100) * 1.20;

    /* On enregistre le retour */
    c->lignes[pos].quantiteRetournee += q;

    /* Le produit revient dans le stock */
    int p = rechercheProduit(b, ref);
    b->produits[p].quantiteStock += q;

    /* On ajoute l'avoir au client */
    b->clients[iClient].avoir += montant;

    printf("Retour est enregistre. Avoir de %.2f EUR est ajoute au client.\n", montant);
    printf("Avoir total du client : %.2f EUR\n", b->clients[iClient].avoir);
}

void afficherAvoir(Boutique *b)
{
    printf("ID du client : ");
    int id = lireEntier(1, 1000000);

    int pos = rechercheClient(b, id);
    if (pos == -1)
    {
        printf("Client introuvable.\n");
        return;
    }

    printf("%s %s : avoir de %.2f EUR\n", b->clients[pos].prenom,
           b->clients[pos].nom, b->clients[pos].avoir);
}


