#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../const.h"
#include "../ball/ball.h"

#define PLAYER_SPEED 20
#define PLAYER_ACC 1
#define PLAYER_MAX_ACC 3
#define PLAYERWIDTH 42
#define PLAYERHEIGHT 62

typedef struct player{
    int x;
    int y;
    enum DIRECTION dir;
    int w;
    int h;
    enum EQUIPE equipe;
}player_t;

typedef struct ordinateur
{
    player_t player;
    float QTable[NBETATS][NBACTIONS];
} ordinateur_t;

void movePlayer(player_t * p, enum DIRECTION dir);
player_t *createPlayer();
void actionPlayer(player_t *player, SDL_Keycode key);
void initQTableOrdi(ordinateur_t *ordi);;
void playerBallCollision(player_t *p, ball_t *b);

#endif