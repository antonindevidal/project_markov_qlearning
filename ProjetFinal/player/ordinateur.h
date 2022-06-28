#ifndef ORDINATEUR_H
#define ORDINATEUR_H
#include "player.h"


typedef struct ordinateur
{
    player_t *player;
    float QTable[NBETATS][NBACTIONS];
} ordinateur_t;



void initQTableOrdi(ordinateur_t *ordi);
ordinateur_t* creerOrdi(enum EQUIPE equipe);
void libererOrdi(ordinateur_t *ordi);


#endif