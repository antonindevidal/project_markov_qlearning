#ifndef PLAYERAFFICHAGE_H
#define PLAYERAFFICHAGE_H

#include "player.h"

#define SPRITE_PLAYER "resources/player/playerShip.png"
#define SCALE 0.8

int loadPlayerTexture(SDL_Renderer *renderer, player_t *player);
void destroyPlayerTexture(player_t *player);
void afficherVaisseau(SDL_Renderer *renderer, player_t *player);
#endif