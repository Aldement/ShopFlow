//
// Created by aldem on 26.10.2026.
//

#ifndef SHOPFLOW_COMMANDE_H
#define SHOPFLOW_COMMANDE_H
#include "types.h"

void creerCommande(Boutique *b);
void afficherUneCommande(Boutique *b);
void changerStatut(Boutique *b);
void annulerCommande(Boutique *b);
void ajouterLigne(Boutique *b);
void supprimerLigne(Boutique *b);
int trouverCommande(Boutique *b, int num, int *iClient, int *iCommande);

#endif //SHOPFLOW_COMMANDE_H
