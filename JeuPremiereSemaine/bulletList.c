#include "bulletList.h"

listB_t initListeBullet() { return NULL; }

int IsVideB(maillonB_t *tete) { return tete == NULL; }

listB_t ajoutEnTeteBullet(int x, int y, listB_t tete)
{
    maillonB_t *nouv = (maillonB_t *)malloc(sizeof(maillonB_t));
    nouv->bullet = createBullet(x, y);
    nouv->suiv = tete;
    return nouv;
}

void supprimerEnTeteListeB(listB_t *prec)
{
    listB_t tmp=*prec;
    *prec=(*prec)->suiv;

    free(tmp->bullet);
    free(tmp);
}


void moveAllBullet(listB_t *tete)
{
    listB_t prec=*tete;
    listB_t cour=NULL;
    int result=moveBullet(&prec->bullet);

    while(result){
        *tete=prec->suiv;
        free(prec->bullet);
        free(prec);
        prec=*tete;
        if(prec!=NULL)cour=prec->suiv;
        result=moveBullet(&prec->bullet);
    }
    if(prec!=NULL){
        cour=prec->suiv;
    }
    

    while (cour != NULL)
    {
        if (moveBullet(&cour->bullet)){
            supprimerEnTeteListeB(&prec);
        }
        else{
            prec = cour;
            cour = cour->suiv;
        }
    }
}

void afficherAllBullet(SDL_Renderer *renderer, listB_t tete, SDL_Texture *texture){
    listB_t cour = tete;
    while (cour != NULL)
    {
        afficherBullet(renderer, cour->bullet, texture);
        cour = cour->suiv;
    }
}
