
#include <stdio.h>
#include <stdlib.h>
#include "../include/types.h"
#include "../include/menu.h"
#include "../include/initialisation.h"

int main(void)
{
    Boutique b;

    initialiserDonneesTest(&b);   /* charge les donnees de demo */
    lancerMenu(&b);               /* affiche les menus */
    detruireBoutique(&b);         /* libere toute la memoire */

    return 0;
}