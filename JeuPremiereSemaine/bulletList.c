#include "bulletList.h"

listB_t initListeBullet() { return NULL; }

int IsVideB(maillonB_t *tete) { return tete == NULL; }

void ajoutEnTeteBullet(int x, int y, listB_t *tete)
{
    maillonB_t *nouv = (maillonB_t *)malloc(sizeof(maillonB_t));
    nouv->bullet = createBullet(x, y);
    nouv->suiv = *tete;
    *tete = nouv;
}


void suppressionBulletFromList(listB_t *tete, maillonB_t *elmt)
{
    maillonB_t **cour = tete,**prec = tete;
    while(*cour != NULL && *cour != elmt)
    {
        prec = &(*prec)->suiv;
        cour = &((*cour)->suiv);
    }
    if (*cour != NULL)
    {
        bullet_t * a = (*cour)->bullet;
        maillonB_t * b;
        b = *cour;
        *prec = (*cour)-> suiv;
        free(a);
        free(b);
    }

}

void moveAllBullet(listB_t *tete)
{

    maillonB_t *cour = *tete,*temp =NULL;
    while (cour != NULL)
    {
        if (moveBullet(cour->bullet))
        {
            // Suppression
            temp = cour->suiv;
            suppressionBulletFromList(tete,cour);
            cour = temp;
        }else
        {
            cour = cour->suiv;
        }
    }
}

void afficherAllBullet(SDL_Renderer *renderer, listB_t tete, SDL_Texture *texture)
{
    listB_t cour = tete;
    while (cour != NULL)
    {
        afficherBullet(renderer, cour->bullet, texture);
        cour = cour->suiv;
    }
}
