#ifndef END_SCREEN_H
#define END_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "../fonctionsSDL.h"
#include "../player/player.h"
#include "../ball/ball.h"

void ecranFin(SDL_Window *window, TTF_Font *font, SDL_Renderer *renderer, SDL_Event event, int *score1, int *score2, player_t *p,ball_t * b, int *debutTimer, int *etat, SDL_bool *programON, Mix_Music *musiqueJeu);

#endif