//
// Created by aldem on 26.10.2026

/*C'est le fichier qui declare tous les structures partagees (Date, Adresse, Produit,
Ligne_commande, Comande, Client, Boutique)  et des constantes ; inclus par tous
les modules pour éviter les inclusions circulaires entre client.h et commande.h.
*/

#ifndef MENUPROJET_TYPES_H
#define MENUPROJET_TYPES_H
typedef struct {
    int jour; // Jour du mois //
    int mois; // Mois de l'annee //
    int annee; // Annee de la commande //
} Date;

typedef struct {
    char rue[80]; // Numero et libelle de voie //
    char ville[50]; // Ville de livraison //
    char codePostal[6]; // Code postal //
    char pays[50]; //pays de livraison //
} Adresse;

typedef struct {
    char reference[12]; // Reference commerciale (SKU) //
    char designation[60]; // Libelle du produit //
    char categorie[30]; // Famille de produit //
    float prixUnitaireHT; // Prix unitaire hors taxes //
    int quantiteStock; // Stock disponible //
    int seuilAlerte; // Seuil de reapprovisionnement //
    int actif; // Statut du produit //
} Produit;

typedef struct {
    char refProduit[12]; // Reference du produit commande //
    char designation[60]; // Libelle fige au moment de la vente //
    int quantite; // Quantite commande //
    float prixUnitaire; // prix fige au moment de la vente //
    float sousTotalHT; // Quantite x prixUnitaireHT //
} Ligne_Commande;

typedef struct {
    int numero; // Numero de commande //
    int idClient; // Reference du client proprietaire //
    Date dateCommande; // Date de validation de la commande //
    char statut[20]; // Etat d'avancement de la commande //
    int nbLignes; // Nombre de lignes reelement saisies //
    int capaciteLignes;  // Taille du tableau alloue //
    Ligne_Commande *lignes; // Tableau de lignes de commande //
    float montantBrutHT; // Some des sous-totaux des lignes, avant remise //
    float tauxRemise; // Taux du palier, déterminé sur le montant HT brut //
    float montantRemise; // montantBrutHT × tauxRemise / 100 //
    float montantHT; // montantBrutHT - montantRemise //
    float montantTVA; // 20% du montant HT //
    float montantTTC; // HT + TVA + frais de port //
    float fraisPort; // Frais de port appliques //
    Adresse adresseLivraisn; // Instante de l'addresse de livraison au moment de la commande //
} Commande;

typedef struct {
    int idClient;              // Identifiant du client (unique, > 0) //
    char nom[50];              // Nom de famille (non vide, 49 car. max) //
    char prenom[50];           // Prénom (non vide) //
    char email[80];            // Adresse électronique (contient '@', unique) //
    char telephone[15];        // Téléphone de contact (10 chiffres) //
    Adresse adresse;           // Adresse de livraison (structure imbriquée) //
    int pointsFidelite;        // Points de fidélité cumulés (>= 0, calculé) //
    int nbCommandes;           // Nombre de commandes du client (>= 0) //
    int capaciteCommandes;     // Taille du tableau alloué (>= nbCommandes) //
    Commande *commandes;       // Historique des commandes (alloué dynamiquement, malloc) //
    int actif;                 // Statut du client : 0 ou 1 (suppression logique) //
} Client;

typedef struct {
    char nom[50];              // Nom commercial de la boutique (non vide) //
    Produit *produits;         // Catalogue des produits (alloué dynamiquement, malloc) //
    int nbProduits;            // Nombre de produits au catalogue (>= 0) //
    int capaciteProduits;      // Capacité allouée du catalogue (>= nbProduits) //
    Client *clients;           // Répertoire des clients (alloué dynamiquement, malloc) //
    int nbClients;             // Nombre de clients enregistrés (>= 0) //
    int capaciteClients;       // Capacité allouée du répertoire (>= nbClients) //
    int numeroSuivant;         // Compteur d'attribution des numéros de commande (> 0) //
    int idClientSuivant;       // Compteur d'attribution des identifiants clients (> 0) //
} Boutique;

#endif //MENUPROJET_TYPES_H