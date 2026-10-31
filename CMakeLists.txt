cmake_minimum_required(VERSION 4.3)
project(ShopFlow C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(include)

add_executable(ShopFlow src/main.c
        src/menu.c
        include/menu.h
        src/initialisation.c
        include/initialisation.h
        include/Types.h
        src/produits.c
        include/produits.h
        src/clients.c
        include/clients.h
        src/statistic.c
        include/statistic.h
        src/utils.c
        include/utils.h)
