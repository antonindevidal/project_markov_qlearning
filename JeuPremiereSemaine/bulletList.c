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
    maillonB_t **cour = tete, **prec = tete;
    while (*cour != NULL && *cour != elmt)
    {
        prec = &(*prec)->suiv;
        cour = &((*cour)->suiv);
    }
    if (*cour != NULL)
    {
        bullet_t *a = (*cour)->bullet;
        maillonB_t *b;
        b = *cour;
        *prec = (*cour)->suiv;
        free(a);
        free(b);
    }
}

void moveAllBullet(listB_t *tete)
{

    maillonB_t *cour = *tete, *temp = NULL;
    while (cour != NULL)
    {
        if (moveBullet(cour->bullet))
        {
            // Suppression
            temp = cour->suiv;
            suppressionBulletFromList(tete, cour);
            cour = temp;
        }
        else
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

// gére les collisions
void collision(listB_t *listeBullet, listEnnemis_t *listeEnnemi, int *score)
{
    ennemi_t *ennemiCour = *listeEnnemi, *tmpEnnemi;
    maillonB_t *bulletCour;
    int distance = 0, diametre = 0;
    while (ennemiCour != NULL && listeBullet != NULL)
    {
        bulletCour = *listeBullet;
        diametre = ennemiCour->infoEnnemi->w / 2 + BULLET_HEIGHT / 2;
        while (bulletCour != NULL)
        {
            // distance entre les deux entités
            distance = sqrt(pow(bulletCour->bullet->x - ennemiCour->infoEnnemi->x, 2) + pow(bulletCour->bullet->y - ennemiCour->infoEnnemi->y, 2));
            // collison
            if (distance < diametre)
            {
                (*score)++;
                suppressionBulletFromList(listeBullet, bulletCour);
                tmpEnnemi = ennemiCour->ennemiSuivant;
                mortEnnemi(listeEnnemi, ennemiCour);
                ennemiCour = tmpEnnemi;
                bulletCour = NULL;
            }
            else
            {
                bulletCour = bulletCour->suiv;
            }
        }
        if (ennemiCour != NULL)
            ennemiCour = ennemiCour->ennemiSuivant;
    }
}

void liberationBullets(listB_t tf)
{
    if (tf != NULL)
    {
        if (tf->suiv != NULL)
        {
            liberationBullets(tf->suiv);
        }
        bullet_t *t = tf->bullet;
        free(t);
        free(tf);
    }
}