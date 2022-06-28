#ifndef ORDINATEUR_H
#define ORDINATEUR_H
#include "player.h"


typedef struct ordinateur
{
    player_t *player;
    float **QTable;
} ordinateur_t;



void initQTableOrdi(ordinateur_t *ordi);
ordinateur_t* creerOrdi(enum EQUIPE equipe);



#endif