#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include <SDL2/SDL_image.h>
#include "const.h"
#define SPEED 8

typedef struct player{
    int x;				//position x
    int y;				//position y
    SDL_Texture *texture;
    int w;
    int h;
}player_t;


void destroyPlayer(player_t *player);
void movePlayerDown(player_t * player);
void movePlayerUp(player_t * player);

#endif