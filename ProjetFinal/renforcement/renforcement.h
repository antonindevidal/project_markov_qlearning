#ifndef __RENFORCEMENT_H__
#define __RENFORCEMENT_H__
#include "../const.h"
#include "../ball/ball.h"
#include "../player/player.h"
#include <math.h>
#include <stdlib.h>

typedef struct ordinateur
{
    int x;
    int y;
    float QTable[NBETATS][NBACTIONS];
} ordinateur_t;

/* Déclaration des prototypes */

void perception(); // Prend l'état du monde et renvoie l'état de perception s
void evolution(ordinateur_t *ordi, int *suiteEtats, int *suiteActions, int *suiteRecompenses, int n);
int recompense(ball_t precBall, ball_t ball, player_t precPlayer, player_t player, int isGoal);
int *enumerationActions(int *tailleActions); // Prend le monde et renvoie une énumération des actions possibles
int choixAction(ordinateur_t *ordi, int s, int T, int tailleActions);
void renforcement(); // Fonction principale

#endif
