#ifndef __ENNEMIS_H__
#define __ENNEMIS_H__
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

void deplacement(int *x, int *y, float theta, float vitesseX, float vitesseY);
void nouveau_theta(float *theta);

#endif
