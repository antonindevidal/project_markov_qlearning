#ifndef __MENUS_H__
#define __MENUS_H__
#include "fonctionsSDL.h"

void menuDebut(TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer);
void menuFin(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer);

#endif