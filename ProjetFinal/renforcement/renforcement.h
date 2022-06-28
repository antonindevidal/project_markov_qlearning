#ifndef __RENFORCEMENT_H__
#define __RENFORCEMENT_H__
#include "../const.h"
#include "../ball/ball.h"
#include "../player/player.h"
#include "../player/ordinateur.h"
#include <math.h>
#include <stdlib.h>

/* Déclaration des prototypes */
int perception(ball_t ball,player_t player, player_t player2); // Prend l'état du monde et renvoie l'état de perception s
void evolution(ordinateur_t *ordi, int *suiteEtats, int *suiteActions, int *suiteRecompenses, int n);
int recompense(ball_t precBall, ball_t ball, player_t precPlayer, player_t player, int isGoal, enum EQUIPE equipeBut);
int choixAction(ordinateur_t *ordi, int s, int T);
void renforcement(ordinateur_t *ordi1, ordinateur_t *ordi2); // Fonction principale
int distanceAdversaire(ball_t ball, player_t player);
void resetEmplacement(ordinateur_t *ordi);
void saveQTable(char *nom_fichier, float QTable[NBETATS][NBACTIONS]);
void chargerQTable(char *nom_fichier, float Qtable[NBETATS][NBACTIONS]);
void copie(player_t *prec, player_t *ordi);

#endif
