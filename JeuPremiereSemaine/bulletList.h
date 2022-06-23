#ifndef BULLET_LIST
#define BULLET_LIST

#include "bulletAffichage.h"
#include "ennemis.h"

typedef struct bulletList
{
    bullet_t *bullet;
    struct bulletList *suiv;
} maillonB_t, *listB_t;

listB_t initListeBullet();
int IsVideB(maillonB_t *tete);
void ajoutEnTeteBullet(int x, int y, listB_t *tete);
void supprimerEnTeteListeB(listB_t *tete);
void moveAllBullet(listB_t *tete);
void afficherAllBullet(SDL_Renderer *renderer, listB_t tete, SDL_Texture *texture);
void collision(listB_t *listeBullet, listEnnemis_t *listeEnnemi, int *score);
void liberationBullets(listB_t tf);
#endif