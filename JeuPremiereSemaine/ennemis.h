#ifndef __ENNEMIS_H__
#define __ENNEMIS_H__
#include <math.h>
#include "fonctionsSDL.h"
#define TAILLE_MARKOV 5

/* Structure ennemis */
typedef struct infoEnnemi
{
    int x;
    int y;
    int w;
    int h;
    int vitesseX;
    int vitesseY;
    int theta;
} infoEnnemi_t;

typedef struct ennemi
{
    infoEnnemi_t *infoEnnemi;
    struct ennemi *ennemiSuivant;
} ennemi_t, *listEnnemis_t;

typedef struct ennemis
{
    ennemi_t *tete;
} ennemis_t;

/* Déclaration des prototypes */
void deplacementEnnemi(int *x, int *y, int theta, float vitesseX, float vitesseY);
void deplacementEnnemis(ennemis_t *tf);
void initEnnemi(ennemis_t *tf);
void ajoutEnnemi(ennemis_t *tf, int x, int y, int w, int h, int vitesseX, int vitesseY);
void mortEnnemi(ennemis_t *tf, ennemi_t *ennemiATuer);
ennemis_t *ennemiToucher(ennemis_t *tf, int tirX, int tirY, int tirW, int tirH); // Retourne l'ennemi à tuer
void afficherEnnemis(ennemis_t *tf, SDL_Texture *texture, SDL_Renderer *renderer);
void liberationEnnemis(ennemi_t *tf);
void nouveauTheta(int *theta);

#endif
