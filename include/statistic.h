//
// Created by aldem on 31.10.2026.
//
#ifndef STATISTIC_H
#define STATISTIC_H
#include "types.h"

void chiffreAffairesTotal(Boutique *b);
void chiffreAffairesParAnnee(Boutique *b, int annee);
void chiffreAffairesParMois(Boutique *b, int mois, int annee);
void alertesStock(Boutique *b);
void topProduits(Boutique *b);
double calculCAClient(Client c);
void palmaresClients(Boutique *b);

#endif