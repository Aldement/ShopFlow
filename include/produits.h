//
// Created by aldem on 31.10.2026.
//

#ifndef SHOPFLOW_PRODUITS_H
#define SHOPFLOW_PRODUITS_H
#include "types.h"

int rechercheProduit(Boutique *b, char ref[]);
void ajouterProduit(Boutique *b);
void modifierProduit(Boutique *b);
void supprimerProduit(Boutique *b);
void afficherCatalogue(Boutique *b);
void rechercherProduit(Boutique *b);

#endif //SHOPFLOW_PRODUITS_H
