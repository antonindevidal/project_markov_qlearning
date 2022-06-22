#ifndef __ENNEMIS_H__
#define __ENNEMIS_H__
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

/* Structure ennemis */
typedef struct ennemi
{
    int x;
    int y;
    int w;
    int h;
} ennemi_t;

typedef struct ennemis
{
    ennemi *info_ennemi;
    struct ennemis *ennemi_suivant;
} ennemis_t;

/* Déclaration des prototypes */
void
deplacement(int *x, int *y, float theta, float vitesseX, float vitesseY);
void nouveau_theta(float *theta);

#endif
