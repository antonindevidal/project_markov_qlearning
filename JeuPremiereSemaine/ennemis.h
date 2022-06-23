#ifndef __ENNEMIS_H__
#define __ENNEMIS_H__
#include <math.h>
#include "fonctionsSDL.h"
#include "const.h"


#define TAILLE_MARKOV 5
#define TAILLEENNEMI 72

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
    int sommeTheta;
} infoEnnemi_t;

typedef struct ennemi
{
    infoEnnemi_t *infoEnnemi;
    struct ennemi *ennemiSuivant;
} ennemi_t, *listEnnemis_t;

/* Déclaration des prototypes */
void deplacementEnnemi(int *x, int *y, int *theta, int *thetaCour, float vitesseX, float vitesseY, int *retour);
int deplacementEnnemis(listEnnemis_t *tf,int calculAngle);
void initEnnemi(listEnnemis_t *tf);
void ajoutEnnemi(listEnnemis_t *tf, int x, int y, int w, int h, int vitesseX, int vitesseY);
void mortEnnemi(listEnnemis_t *tf, ennemi_t *ennemiATuer);
void afficherEnnemis(listEnnemis_t tf, SDL_Texture *texture, SDL_Renderer *renderer);
void liberationEnnemis(listEnnemis_t tf);
void nouveauTheta(int *theta);
void spawnEnnemi(listEnnemis_t *l);
#endif
