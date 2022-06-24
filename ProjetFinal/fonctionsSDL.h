#ifndef __FONCTIONS_SDL_H__
#define __FONCTIONS_SDL_H__
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "const.h"

/* DECLARATION DES PROTOTYPES */

void endSDL(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *loadTextureFromImage(char *fileImageName, SDL_Window *window, SDL_Renderer *renderer);
void afficherTexture(SDL_Texture *maTexture, SDL_Renderer *renderer, int w, int h, int x, int y);

#endif
