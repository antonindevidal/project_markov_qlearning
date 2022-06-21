#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>


void afficherGrille(int ** nouv,int tailleX, int tailleY,int tailleCell,SDL_Renderer *renderer);
void afficherCase(SDL_Renderer* renderer, int value, int posX, int posY, int tailleCell);

#endif