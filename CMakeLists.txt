cmake_minimum_required(VERSION 4.3)
project(ShopFlow C)

set(CMAKE_C_STANDARD 23)


include_directories(include)

add_executable(ShopFlow src/main.c
        src/menu.c
        include/menu.h
        src/Initialisation.c
        include/Initialisation.h
        include/types.h
        src/Produits.c
        include/Produits.h
        src/Clients.c
        include/Clients.h
        "src/Fonction Gestion des produits(ajouterProduit).c"
        "src/Fonction Gestion des produits(modifierProduit(afficherProduits)).c"
        include/commande.h
        src/commande.c)
