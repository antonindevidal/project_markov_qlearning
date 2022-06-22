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
void deplacement(int *x, int *y, float theta, float vitesseX, float vitesseY);
void init_ennemi(ennemis_t * tf)
void ajout_ennemi(ennemis_t * tf, int x, int y, int w, int h)
void mort_ennemi(ennemis_t * tf, ennemis_t * ennemi_a_tuer);
ennemis_t * ennemi_toucher(ennemis_t * tf, int tir_x, int tir_y, int tir_w, int tir_h); //Retourne l'ennemi à tuer
void afficher_ennemis(ennemis_t * tf);
void liberation_ennemis(ennemis_t * tf);
void nouveau_theta(float *theta);

#endif
