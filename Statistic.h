//
// Created by gaelt on 29.10.26.
//

#ifndef SHOPFLOW_STATISTIC_H
#define SHOPFLOW_STATISTIC_H

#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include "types.h"

void chiffreAffairesTotal(Boutique *b);
void chiffreAffairesParMois(Boutique *b, int mois, int annee);
void chiffreAffairesParAnnee(Boutique *b, int annee);

void topProduits(Boutique *b);
void topClients(Boutique *b);

void alertesStock(Boutique *b);

#endif

#endif //SHOPFLOW_STATISTIC_H
