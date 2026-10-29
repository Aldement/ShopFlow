//
// Created by aldem on 26.10.2026.
//

#include "../include/commande.h"
#include "../include/types.h"
#include "../include/produits.h"
#include "../include/Clients.h"
#include "../include/Initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Produit *modele = NULL;
static Commande *commande = NULL;
int tailleCommande = 0;
int tailleModele;


static void creerCommande(void) {
    int client;
    int nb_produits;
    Commande *commande_tmp = realloc(modele, (tailleCommande+1) * sizeof(Commande));
    commande = commande_tmp;
    commande->numero = tailleCommande + 1;
    printf("Saisir l'identifiand du client: ");
    scanf("%d", &client);
    commande->idClient = client;
    printf("Saisir la date de commande (Jour, Mois, Annee): ");
    scanf("%d, %d, %d", &commande->dateCommande.jour, &commande->dateCommande.mois, &commande->dateCommande.annee);
    strcpy(commande->statut, "EN_COURS");
    printf("Saisir le nombre de produits a commander: ");
    scanf("%d", &nb_produits);
    commande->capaciteLignes = nb_produits + 1;
    commande->lignes = malloc(nb_produits * sizeof(Ligne_Commande));
    for (int i = 0; i < nb_produits; i++) {
        printf("Saisir la reference de produit: ");
        fgets(commande->lignes[i].refProduit, sizeof(commande->lignes[i].refProduit), stdin);
        commande->lignes[i].refProduit[strcspn(commande->lignes[i].refProduit, "\n")] = '\0';
        int j;
        int found = 0;
        for (j = 0; j < tailleModele; j++) {
            if (strcmp(commande->lignes[i].refProduit, modele[j].reference) == 0) {
                strcpy(commande->lignes[i].designation, modele[j].designation);
                commande->lignes[i].prixUnitaire = modele[j].prixUnitaireHT;
                found = 1;
                break;
            }
        }
        if (found == 0) printf("Le produit de cette reference n'existe pas");

        do {
            printf("Saisir le quantite de produit: ");
            scanf("%d", &commande->lignes[i].quantite);
            if (commande->lignes[i].quantite > modele[j].quantiteStock) {
                printf("Il n'y a pas assez de ces produits pour votre commande, saisissez le quantite plus petite.\n");
            }
        } while (commande->lignes[i].quantite > modele[j].quantiteStock);
        commande->lignes[i].sousTotalHT = commande->lignes[i].quantite * commande->lignes[i].prixUnitaire;
        commande->montantBrutHT += commande->lignes[i].sousTotalHT;
    }
    int tauxRemise;
    if (commande->montantBrutHT < 100)
        tauxRemise = 0;
    else if (commande->montantBrutHT < 299.99)
        tauxRemise = 5;
    else if (commande->montantBrutHT < 599.99)
        tauxRemise = 10;
    else tauxRemise = 20;
    commande->montantRemise = commande->montantBrutHT * tauxRemise / 100;
    commande->montantHT = commande->montantBrutHT - commande->montantRemise;
    commande->montantTVA = 0.2 * commande->montantHT;
    if (commande->montantBrutHT >= 60)
        commande->fraisPort = 5.9;
    else commande->fraisPort = 0;
    commande->montantTTC = commande->montantHT + commande->montantTVA + commande->fraisPort;
    printf("Saisir l'adresse de livraison (rue, ville, code postal, pays): ");
    fgets(commande->adresseLivraisn.rue, 80, stdin);
    commande->adresseLivraisn.rue[strcspn(commande->adresseLivraisn.rue, "\n")] = '\0';
    fgets(commande->adresseLivraisn.ville, 50, stdin);
    commande->adresseLivraisn.ville[strcspn(commande->adresseLivraisn.ville, "\n")] = '\0';
    scanf("%s", commande->adresseLivraisn.codePostal);
    fgets(commande->adresseLivraisn.pays, 50, stdin);
    commande->adresseLivraisn.pays[strcspn(commande->adresseLivraisn.pays, "\n")] = '\0';
    tailleCommande++;
}
