#ifndef __FONCTIONS_SDL_H__
#define __FONCTIONS_SDL_H__
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

/* DECLARATION DES PROTOTYPES */

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int pos, int couleur, int couleur_arc);

#endif
