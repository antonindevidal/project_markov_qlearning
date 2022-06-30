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
//void afficherQTable(ordinateur_t *ordi);
void libererOrdi(ordinateur_t *ordi);
void afficherQTable(float **tab,int n,int m);



#endif