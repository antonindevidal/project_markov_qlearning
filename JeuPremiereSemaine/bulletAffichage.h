#ifndef BULLET_AFFICHAGE
#define BULLET_AFFICHAGE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bullet.h"

#define SPRITE_BULLET "resources/player/laserBlue02.png"

void afficherBullet(SDL_Renderer *renderer, bullet_t *bullet,SDL_Texture *texture);
int loadBulletTexture(SDL_Renderer *renderer, SDL_Texture **texture);


#endif