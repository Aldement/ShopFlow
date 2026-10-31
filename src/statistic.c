#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/Statistic.h"
#include "../include/Produits.h"

void chiffreAffairesTotal(Boutique *b){
    double totalHT = 0;
    double totalTTC = 0;

    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            Commande *c = &b->clients[i].commandes[j];

            if (strcmp(c->statut, "ANNULEE") != 0){
                totalHT = totalHT + c->montantHT;
                totalTTC = totalTTC + c->montantTTC;
            }
        }
    }

    printf("\nCA HT  : %.2f EUR", totalHT);
    printf("\nCA TTC : %.2f EUR\n", totalTTC);
}

void chiffreAffairesParAnnee(Boutique *b, int annee){
    double totalHT = 0;
    double totalTTC = 0;

    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            Commande *c = &b->clients[i].commandes[j];

            if (strcmp(c->statut, "ANNULEE") != 0 && c->dateCommande.annee == annee){
                totalHT = totalHT + c->montantHT;
                totalTTC = totalTTC + c->montantTTC;
            }
        }
    }

    printf("\nCA %d : %.2f EUR HT, %.2f EUR TTC\n", annee, totalHT, totalTTC);
}

void chiffreAffairesParMois(Boutique *b, int mois, int annee){
    double totalHT = 0;
    double totalTTC = 0;

    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            Commande *c = &b->clients[i].commandes[j];

            if (strcmp(c->statut, "ANNULEE") != 0
                && c->dateCommande.mois == mois
                && c->dateCommande.annee == annee){
                totalHT = totalHT + c->montantHT;
                totalTTC = totalTTC + c->montantTTC;
            }
        }
    }

    printf("\nCA %02d/%d : %.2f EUR HT, %.2f EUR TTC\n", mois, annee, totalHT, totalTTC);
}

void alertesStock(Boutique *b){
    int trouve = 0;

    printf("\n=== ALERTES STOCK ===\n");

    for (int i = 0; i < b->nbProduits; i++){
        if (b->produits[i].actif == 1
            && b->produits[i].quantiteStock <= b->produits[i].seuilAlerte){
            printf("%s - %s : stock %d (seuil %d)\n",
                   b->produits[i].reference, b->produits[i].designation,
                   b->produits[i].quantiteStock, b->produits[i].seuilAlerte);
            trouve = 1;
        }
    }

    if (trouve == 0) printf("Aucune alerte.\n");
}

void topProduits(Boutique *b){
    if (b->nbProduits == 0){
        printf("Aucun produit.\n");
        return;
    }

    /* ventes[i] = quantite vendue du produit i ; ordre[] = positions a trier */
    int *ventes = malloc(b->nbProduits * sizeof(int));
    int *ordre = malloc(b->nbProduits * sizeof(int));

    if (ventes == NULL || ordre == NULL){
        printf("Erreur memoire.\n");
        free(ventes);
        free(ordre);
        return;
    }

    for (int i = 0; i < b->nbProduits; i++){
        ventes[i] = 0;
        ordre[i] = i;
    }

    /* on compte les ventes (commandes non annulees seulement) */
    for (int i = 0; i < b->nbClients; i++){
        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            Commande *c = &b->clients[i].commandes[j];

            if (strcmp(c->statut, "ANNULEE") != 0){
                for (int k = 0; k < c->nbLignes; k++){
                    int p = rechercheProduit(b, c->lignes[k].refProduit);
                    if (p != -1) ventes[p] = ventes[p] + c->lignes[k].quantite;
                }
            }
        }
    }

    /* tri a bulles : le plus vendu en premier */
    for (int i = 0; i < b->nbProduits - 1; i++){
        for (int j = 0; j < b->nbProduits - 1 - i; j++){
            if (ventes[ordre[j]] < ventes[ordre[j + 1]]){
                int temp = ordre[j];
                ordre[j] = ordre[j + 1];
                ordre[j + 1] = temp;
            }
        }
    }

    printf("\n=== TOP 5 PRODUITS ===\n");
    for (int i = 0; i < 5 && i < b->nbProduits; i++){
        printf("%d. %s (%d vendus)\n", i + 1,
               b->produits[ordre[i]].designation, ventes[ordre[i]]);
    }

    free(ventes);
    free(ordre);
}

/* CA TTC d'un client, sans les commandes annulees */
double calculCAClient(Client c){
    double total = 0;

    for (int i = 0; i < c.nbCommandes; i++){
        if (strcmp(c.commandes[i].statut, "ANNULEE") != 0)
            total = total + c.commandes[i].montantTTC;
    }

    return total;
}

void palmaresClients(Boutique *b){
    if (b->nbClients == 0){
        printf("Aucun client.\n");
        return;
    }

    double *ca = malloc(b->nbClients * sizeof(double));
    int *ordre = malloc(b->nbClients * sizeof(int));

    if (ca == NULL || ordre == NULL){
        printf("Erreur memoire.\n");
        free(ca);
        free(ordre);
        return;
    }

    for (int i = 0; i < b->nbClients; i++){
        ca[i] = calculCAClient(b->clients[i]);
        ordre[i] = i;
    }

    /* meme tri a bulles que pour les produits */
    for (int i = 0; i < b->nbClients - 1; i++){
        for (int j = 0; j < b->nbClients - 1 - i; j++){
            if (ca[ordre[j]] < ca[ordre[j + 1]]){
                int temp = ordre[j];
                ordre[j] = ordre[j + 1];
                ordre[j + 1] = temp;
            }
        }
    }

    printf("\n=== PALMARES CLIENTS ===\n");
    for (int i = 0; i < b->nbClients; i++){
        printf("%d. %s %s : %.2f EUR\n", i + 1,
               b->clients[ordre[i]].prenom, b->clients[ordre[i]].nom, ca[ordre[i]]);
    }

    free(ca);
    free(ordre);
}