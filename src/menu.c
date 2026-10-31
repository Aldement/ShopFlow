#include <stdio.h>
#include "../include/types.h"
#include "../include/menu.h"
#include "../include/utils.h"
#include "../include/produits.h"
#include "../include/clients.h"
#include "../include/Commande.h"
#include "../include/statistic.h"

static void menuProduits(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES PRODUITS =====\n");
        printf("  1. Ajouter un produit\n");
        printf("  2. Modifier un produit\n");
        printf("  3. Supprimer un produit\n");
        printf("  4. Afficher le catalogue\n");
        printf("  5. Rechercher un produit\n");
        printf("  0. Retour\n");
        printf("  Votre choix : ");
        choix = lireEntier(0, 5);

        if (choix == 1) ajouterProduit(b);
        if (choix == 2) modifierProduit(b);
        if (choix == 3) supprimerProduit(b);
        if (choix == 4) afficherCatalogue(b);
        if (choix == 5) rechercherProduit(b);
    } while (choix != 0);
}

static void menuClients(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES CLIENTS =====\n");
        printf("  1. Ajouter un client\n");
        printf("  2. Modifier un client\n");
        printf("  3. Supprimer un client\n");
        printf("  4. Afficher la liste des clients\n");
        printf("  5. Afficher un client\n");
        printf("  0. Retour\n");
        printf("  Votre choix : ");
        choix = lireEntier(0, 5);

        if (choix == 1) ajouterClient(b);
        if (choix == 2) mettreAJourClient(b);
        if (choix == 3) supprimerClient(b);
        if (choix == 4) afficherlisteClient(b);
        if (choix == 5) afficherClient(b);
    } while (choix != 0);
}

static void menuCommandes(Boutique *b)
{
    int choix;
    do
    {
        printf("\n===== GESTION DES COMMANDES =====\n");
        printf("  1. Creer une commande\n");
        printf("  2. Afficher une commande\n");
        printf("  3. Ajouter une ligne\n");
        printf("  4. Supprimer une ligne\n");
        printf("  5. Changer le statut\n");
        printf("  6. Annuler une commande\n");
        printf("  0. Retour\n");
        printf("  Votre choix : ");
        choix = lireEntier(0, 6);

        if (choix == 1) creerCommande(b);
        if (choix == 2) afficherUneCommande(b);
        if (choix == 3) ajouterLigne(b);
        if (choix == 4) supprimerLigne(b);
        if (choix == 5) changerStatut(b);
        if (choix == 6) annulerCommande(b);
    } while (choix != 0);
}

static void menuStatistiques(Boutique *b)
{
    int choix;
    int mois, annee;
    do
    {
        printf("\n===== STATISTIQUES =====\n");
        printf("  1. Chiffre d'affaires total\n");
        printf("  2. Chiffre d'affaires d'une annee\n");
        printf("  3. Chiffre d'affaires d'un mois\n");
        printf("  4. Top 5 des produits\n");
        printf("  5. Palmares des clients\n");
        printf("  6. Alertes de stock\n");
        printf("  0. Retour\n");
        printf("  Votre choix : ");
        choix = lireEntier(0, 6);

        if (choix == 1) chiffreAffairesTotal(b);
        if (choix == 2)
        {
            printf("Annee : ");
            annee = lireEntier(2000, 2100);
            chiffreAffairesParAnnee(b, annee);
        }
        if (choix == 3)
        {
            printf("Mois : ");
            mois = lireEntier(1, 12);
            printf("Annee : ");
            annee = lireEntier(2000, 2100);
            chiffreAffairesParMois(b, mois, annee);
        }
        if (choix == 4) topProduits(b);
        if (choix == 5) palmaresClients(b);
        if (choix == 6) alertesStock(b);
    } while (choix != 0);
}

void lancerMenu(Boutique *b)
{
    int choix;

    printf("==============================================\n");
    printf("  SHOPFLOW - Boutique en ligne\n");
    printf("==============================================\n");

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("  1. Gestion des produits\n");
        printf("  2. Gestion des clients\n");
        printf("  3. Gestion des commandes\n");
        printf("  4. Statistiques\n");
        printf("  0. Quitter\n");
        printf("  Votre choix : ");
        choix = lireEntier(0, 4);

        if (choix == 1) menuProduits(b);
        if (choix == 2) menuClients(b);
        if (choix == 3) menuCommandes(b);
        if (choix == 4) menuStatistiques(b);
    } while (choix != 0);

    printf("\n  Au revoir !\n");
}