cmake_minimum_required(VERSION 4.3)
project(ShopFlow C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

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
        include/Clients.h)
