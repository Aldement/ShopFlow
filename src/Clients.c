//
// Created by gaelt on 26.10.26.
//

#include "../include/Clients.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"



void ajouterClient(Boutique *b)
{
    char email[100];

    printf("Email : ");
    scanf("%s", email);

    for(int i=0;i<b->nbClients;i++)
    {
        if(strcmp(b->clients[i].email,email)==0)
        {
            printf("Email deja utilise.\n");
            return;
        }
    }

    if(b->nbClients == b->capaciteClients)
    {
        b->capaciteClients *= 2;

        Client *tmp = realloc(b->clients,b->capaciteClients*sizeof(Client));

        if(tmp == NULL)
            return;

        b->clients = tmp;
    }

    Client c;

    c.idClient = b->idClientSuivant++;

    strcpy(c.email,email);

    printf("Nom : ");
    scanf("%s", c.nom);

    printf("Prenom : ");
    scanf("%s", c.prenom);

    printf("Telephone : ");
    scanf("%s", c.telephone);

    printf("Rue : ");
    scanf(" %[^\n]", c.adresse.rue);

    printf("Ville : ");
    scanf(" %[^\n]", c.adresse.ville);

    printf("Code postal : ");
    scanf("%s", c.adresse.codePostal);

    printf("Pays : ");
    scanf(" %[^\n]", c.adresse.pays);

    c.commandes = NULL;
    c.nbCommandes = 0;
    c.capaciteCommandes = 0;
    c.actif = 1;

    b->clients[b->nbClients++] = c;
}

int rechercheClient(Boutique *b, int idClient)
{
    for(int i=0;i<b->nbClients;i++)
    {
        if(b->clients[i].idClient == idClient)
            return i;
    }

    return -1;
}

void mettreAJourClient(Boutique *b)
{
    int id;

    printf("ID client : ");
    scanf("%d",&id);

    int pos = rechercheClient(b,id);

    if(pos == -1)
    {
        printf("Client introuvable.\n");
        return;
    }

    Client *c = &b->clients[pos];

    printf("Nom : ");
    scanf("%s", c->nom);

    printf("Prenom : ");
    scanf("%s", c->prenom);

    printf("Telephone : ");
    scanf("%s", c->telephone);

    printf("Rue : ");
    scanf(" %s", c->adresse.rue);

    printf("Ville : ");
    scanf(" %s", c->adresse.ville);

    printf("Code postal : ");
    scanf("%s", c->adresse.codePostal);

    printf("Pays : ");
    scanf(" %s", c->adresse.pays);

    printf("Client mis a jour.\n");
}

void supprimerClient(Boutique *b)
{
    int id;

    printf("ID client : ");
    scanf("%d",&id);

    int pos = rechercheClient(b,id);

    if(pos == -1)
    {
        printf("Client introuvable.\n");
        return;
    }

    Client *c = &b->clients[pos];

    for(int i=0;i<c->nbCommandes;i++)
    {
        if(c->commandes[i].statut != 0)
        {
            printf("Suppression refusee : commande active.\n");
            return;
        }
    }

    c->actif = 0;

    printf("Client desactive.\n");
}

void afficherClient(Boutique *b)
{
    int id;

    printf("ID client : ");
    scanf("%d",&id);

    int pos = rechercheClient(b,id);

    if(pos == -1)
    {
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

    for(int i=0;i<c.nbCommandes;i++)
    {
        printf("Commande %d - %.2f €\n",c.commandes[i].numero,c.commandes[i].montantTTC);
    }
}
void afficherlisteClient(Boutique* b) {
    printf("\n-------------Liste Clients--------------\n");
    float ca=0;
    for (int i=0;i<b->nbClients++;i++) {
        for (int j=0;j<b->clients[i].nbCommandes;j++) {
            ca += b->clients[i].commandes[j].montantTTC;
        }
        printf("\nID : %d",b->clients[i].idClient);

        printf("\nNom : %s %s",b->clients[i].prenom,b->clients[i].nom);

        printf("\nNb commandes : %d",b->clients[i].nbCommandes);

        printf("\nCA genere : %.2f €\n",ca);
    }

}
