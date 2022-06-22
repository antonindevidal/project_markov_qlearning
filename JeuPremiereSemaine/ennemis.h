#ifndef __ENNEMIS_H__
#define __ENNEMIS_H__
#include <math.h>
#include "fonctions_SDL.h"

/* Structure ennemis */
typedef struct info_ennemi
{
    int x;
    int y;
    int w;
    int h;
    int vitesseX;
    int vitesseY;
    int theta;
} info_ennemi_t;

typedef struct ennemi
{
    info_ennemi_t *info_ennemi;
    struct ennemi *ennemi_suivant;
} ennemi_t;

typedef struct ennemis
{
    ennemi_t *tete;
} ennemis_t;

/* Déclaration des prototypes */
void deplacement_ennemi(int *x, int *y, float theta, float vitesseX, float vitesseY);
void deplacement_ennemis(ennemis_t *tf);
void init_ennemi(ennemis_t *tf);
void ajout_ennemi(ennemis_t *tf, int x, int y, int w, int h, int vitesseX, int vitesseY);
void mort_ennemi(ennemis_t *tf, ennemi_t *ennemi_a_tuer);
ennemis_t *ennemi_toucher(ennemis_t *tf, int tir_x, int tir_y, int tir_w, int tir_h); // Retourne l'ennemi à tuer
void afficher_ennemis(ennemis_t *tf,SDL_Texture *texture, SDL_Renderer *renderer);
void liberation_ennemis(ennemi_t *tf);
void nouveau_theta(int *theta);

#endif
