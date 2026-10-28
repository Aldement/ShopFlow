//
// Created by gaelt on 26.10.26.
//

#ifndef PROJET_C_CLIENTS_H
#define PROJET_C_CLIENTS_H
#include <stdio.h>

#include "types.h"

int rechercherClient(Boutique *b, int);
void ajouterClient(Boutique *b);
void mettreAJourClient(Boutique *b);
void supprimerClient(Boutique *b);
void afficherListeClients(Boutique *b);
void afficherClient(Boutique *b);
#endif //PROJET_C_CLIENTS_H
