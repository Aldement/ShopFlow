//
// Created by gaelt on 29.10.26.
//

#include "Statistic.h"

#include <stdio.h>

void chiffreAffairesTotal(Boutique *b)
{
    float totalHT = 0;

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

