#ifndef __RENFORCEMENT_H__
#define __RENFORCEMENT_H__
#include "const.h"

typedef struct ordinateur
{
    int x;
    int y;
    float QTable[NBETATS][NBACTIONS];
} ordinateur_t;

/* Déclaration des prototypes */

void perception();         // Prend l'état du monde et renvoie l'état de perception s
void evolution();          // Prend le monde et une action et modifie l'état du monde
void recompense();         // Prend le monde et renvoie la récompense associé à cet état
void enumerationActions(); // Prend le monde et renvoie une énumération des actions possibles
int choixAction(ordinateur_t *ordi, int perception);        // Prend une perception et le monde et renvoie l'action choisie
void renforcement();       // Fonction principale

#endif
