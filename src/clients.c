//
// Created by gaelt on 26.10.26.
//

#include "../include/clients.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"


void ajouterClient(Boutique *b){
    char email[80];

    printf("Email : ");
    lireTexte(email, 80);

    for(int i=0; i<b->nbClients; i++){
        if(strcmp(b->clients[i].email, email)==0){
            printf("Email deja utilise.\n");
            return;
        }
    }

    if(b->nbClients == b->capaciteClients){
        b->capaciteClients *= 2;

        Client *tmp = realloc(b->clients,b->capaciteClients*sizeof(Client));

        if(tmp == NULL) return;

        b->clients = tmp;
    }

    Client c;

    c.idClient = b->idClientSuivant;
    b->idClientSuivant++;

    strcpy(c.email,email);

    printf("Nom : ");
    lireTexte(c.nom, 50);

    printf("Prenom : ");
    lireTexte(c.prenom, 50);

    printf("Telephone : ");
    lireTexte(c.telephone, 15);

    printf("Rue : ");
    lireTexte(c.adresse.rue, 80);

    printf("Ville : ");
    lireTexte(c.adresse.ville, 50);

    printf("Code postal : ");
    lireTexte(c.adresse.codePostal, 6);

    printf("Pays : ");
    lireTexte(c.adresse.pays, 50);

    c.pointsFidelite = 0;
    c.commandes = NULL;
    c.nbCommandes = 0;
    c.capaciteCommandes = 0;
    c.actif = 1;
    c.avoir = 0;
    b->clients[b->nbClients++] = c;
}

int rechercheClient(Boutique *b, int idClient){
    for (int i=0; i<b->nbClients; i++){
        if (b->clients[i].idClient == idClient) return i;
    }
    return -1;
}

void mettreAJourClient(Boutique *b){
    int id;

    printf("ID client : ");
    id = lireEntier(1, 1000000);

    int pos = rechercheClient(b, id);

    if(pos == -1){
        printf("Client introuvable.\n");
        return;
    }

    Client *c = &b->clients[pos];

    printf("Nom : ");
    lireTexte(c->nom, 50);

    printf("Prenom : ");
    lireTexte(c->prenom, 50);

    printf("Telephone : ");
    lireTexte(c->telephone, 15);

    printf("Rue : ");
    lireTexte(c->adresse.rue, 80);

    printf("Ville : ");
    lireTexte(c->adresse.ville, 50);

    printf("Code postal : ");
    lireTexte(c->adresse.codePostal, 6);

    printf("Pays : ");
    lireTexte(c->adresse.pays, 50);

    printf("Client mis a jour.\n");
}

void supprimerClient(Boutique *b){
    int id;

    printf("ID client : ");
    id = lireEntier(1, 1000000);

    int pos = rechercheClient(b,id);

    if (pos == -1){
        printf("Client introuvable.\n");
        return;
    }

    Client *c = &b->clients[pos];

    for (int i=0; i<c->nbCommandes; i++){
        if (strcmp(c->commandes[i].statut, "ANNULEE") != 0){
            printf("Suppression refusee : commande active.\n");
            return;
        }
    }

    c->actif = 0;

    printf("Client desactive.\n");
}

void afficherClient(Boutique *b){
    int id;

    printf("ID client : ");
    id = lireEntier(1, 1000000);

    int pos = rechercheClient(b,id);

    if (pos == -1){
        printf("Client introuvable.\n");
        return;
    }

    Client c = b->clients[pos];

    printf("\n===== FICHE CLIENT =====\n");

    printf("ID : %d\n", c.idClient);
    printf("Nom : %s\n", c.nom);
    printf("Prenom : %s\n", c.prenom);
    printf("Email : %s\n", c.email);
    printf("Telephone : %s\n", c.telephone);

    printf("\nAdresse\n");
    printf("%s\n", c.adresse.rue);
    printf("%s %s\n",c.adresse.codePostal,c.adresse.ville);
    printf("%s\n", c.adresse.pays);

    printf("\nHistorique des commandes\n");

    for (int i=0; i<c.nbCommandes; i++){
        printf("Commande %d - %.2f €\n",c.commandes[i].numero,c.commandes[i].montantTTC);
    }

    printf("Avoir : %.2f EUR\n", c.avoir);
}
void afficherlisteClient(Boutique* b){
    printf("\n------------- Liste Clients --------------\n");

    for (int i = 0; i < b->nbClients; i++){
        double ca = 0;   /* remis a zero pour chaque client */

        for (int j = 0; j < b->clients[i].nbCommandes; j++){
            if (strcmp(b->clients[i].commandes[j].statut, "ANNULEE") != 0)
                ca += b->clients[i].commandes[j].montantTTC;
        }

        printf("\nID : %d", b->clients[i].idClient);
        printf("\nNom : %s %s", b->clients[i].prenom, b->clients[i].nom);
        printf("\nNb commandes : %d", b->clients[i].nbCommandes);
        printf("\nCA genere : %.2f EUR\n", ca);
    }
}
