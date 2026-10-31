//
// Created by gaelt on 29.10.26.
//

#include "Statistic.h"
#include "types.h"

#include <stdio.h>

void chiffreAffairesTotal(Boutique *b)
{
    double totalHT = 0;

    for(int i=0;i<b->nbClients;i++)
    {
        for(int j=0;j<b->clients[i].nbCommandes;j++)
        {
            totalHT += b->clients[i].commandes[j].montantHT;
        }
    }

    float totalTTC = totalHT * (1 + TVA);

    printf("\nCA HT : %.2f €", totalHT);
    printf("\nCA TTC : %.2f €\n", totalTTC);

}

void chiffreAffairesParAnnee(Boutique *b, int annee)
{
    float total = 0;

    for(int i=0;i<b->nbClients;i++)
    {
        for(int j=0;j<b->clients[i].nbCommandes;j++)
        {
            if(b->clients[i].commandes[j].dateCommande.annee == annee)
            {
                total += b->clients[i].commandes[j].montantHT;
            }
        }
    }

    printf("CA %d : %.2f €\n", annee, total);
}

void chiffreAffairesParMois(Boutique *b,
                            int mois,
                            int annee)
{
    float total = 0;

    for(int i=0;i<b->nbClients;i++)
    {
        for(int j=0;j<b->clients[i].nbCommandes;j++)
        {
            Commande cmd =
                b->clients[i].commandes[j];

            if(cmd.dateCommande.mois == mois &&
               cmd.dateCommande.annee == annee)
            {
                total += cmd.montantHT;
            }
        }
    }

    printf("CA %02d/%d : %.2f €\n",
           mois,
           annee,
           total);
}

void alertesStock(Boutique *b)
{
    printf("\n=== ALERTES STOCK ===\n");

    for(int i=0;i<b->nbProduits;i++)
    {
        if(b->produits[i].quantiteStock
           <= b->produits[i].seuilAlerte)
        {
            printf("%s - %s\n",
                   b->produits[i].reference,
                   b->produits[i].designation);

            printf("Stock : %d\n",
                   b->produits[i].quantiteStock);

            printf("Seuil : %d\n\n",
                   b->produits[i].seuilAlerte);
        }
    }
}

void topProduits(Boutique *b)
{
    Produit tmp;

    for(int i=0;i<b->nbProduits-1;i++)
    {
        for(int j=i+1;j<b->nbProduits;j++)
        {
            if(b->produits[j].quantiteVendue >
               b->produits[i].quantiteVendue)
            {
                tmp = b->produits[i];
                b->produits[i] = b->produits[j];
                b->produits[j] = tmp;
            }
        }
    }

    printf("\n=== TOP 5 PRODUITS ===\n");

    int limite = b->nbProduits < 5 ?
                 b->nbProduits : 5;

    for(int i=0;i<limite;i++)
    {
        printf("%d. %s (%d ventes)\n",
               i+1,
               b->produits[i].designation,
               b->produits[i].quantiteVendue);
    }
}

float calculCAClient(Client c)
{
    float total = 0;

    for(int i=0;i<c.nbCommandes;i++)
    {
        total += c.commandes[i].montantHT;
    }

    return total;
}