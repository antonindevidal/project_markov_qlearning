#ifndef __SCORE_H__
#define __SCORE_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "fonctionsSDL.h"
#include "const.h"

void afficherScore(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer);

#endif