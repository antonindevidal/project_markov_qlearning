#include "ennemis.h"

int valeursTheta[5]={-20,10,0,10,20};
float matriceTheta[5][5]={
//        -20  -10   0   +10  +20
/*-20*/  {0.6, 0.3, 0.1, 0.0, 0.0},
/*-10*/  {0.3, 0.6, 0.1, 0.0, 0.0},
/*  0*/  {0.3, 0.1, 0.2, 0.1, 0.3},
/*+10*/  {0.0, 0.0, 0.1, 0.6, 0.3}, 
/*+20*/  {0.0, 0.0, 0.1, 0.3, 0.6}};

void deplacement_ennemi(int *x, int *y, int theta, float vitesseX, float vitesseY)
{
    /* Calcul la nouvelle position de l'ennemis */
    *x = *x + cos(theta * M_PI / 180 + M_PI) * vitesseX;
    *y = *y + sin(theta * M_PI / 180 + M_PI) * vitesseY;
}

void deplacement_ennemis(ennemis_t *tf)
{
    if (tf->tete != NULL)
    { // S'il existe des ennemis
        ennemi_t *courant;
        courant = tf->tete;
        int x, y, w, h, vitesseX, vitesseY, theta;
        do {
            w = courant->info_ennemi->w;
            h = courant->info_ennemi->h;
            vitesseX = courant->info_ennemi->vitesseX;
            vitesseY = courant->info_ennemi->vitesseY;
            nouveau_theta(&(courant->info_ennemi->theta));
            theta = courant->info_ennemi->theta;
            deplacement_ennemi(&courant->info_ennemi->x, &courant->info_ennemi->y, theta, vitesseX, vitesseY);
            courant = courant->ennemi_suivant;
        } while (courant->ennemi_suivant != NULL);
        w = courant->info_ennemi->w;
        h = courant->info_ennemi->h;
        vitesseX = courant->info_ennemi->vitesseX;
        vitesseY = courant->info_ennemi->vitesseY;
        nouveau_theta(&(courant->info_ennemi->theta));
        theta = courant->info_ennemi->theta;
        deplacement_ennemi(&courant->info_ennemi->x, &courant->info_ennemi->y, theta, vitesseX, vitesseY);
    }
}

void init_ennemi(ennemis_t *tf)
{
    tf->tete = NULL;
}

void ajout_ennemi(ennemis_t *tf, int x, int y, int w, int h, int vitesseX, int vitesseY)
{
    ennemi_t *nouv_ennemi;
    nouv_ennemi = (ennemi_t *)malloc(sizeof(ennemi_t));
    if (nouv_ennemi != NULL)
    { // Allocation Ok
        nouv_ennemi->ennemi_suivant = NULL;
        info_ennemi_t *info_nouv;
        info_nouv = (info_ennemi_t *)malloc(sizeof(info_ennemi_t));
        if (info_nouv != NULL)
        { // Allocation Ok
            info_nouv->x = x;
            info_nouv->y = y;
            info_nouv->w = w;
            info_nouv->h = h;
            info_nouv->vitesseX = vitesseX;
            info_nouv->vitesseY = vitesseY;
            info_nouv->theta = 10; //On suppose que l'ennemi va tout droit au départ;
        }
        else
        {
            printf("Erreur d'allocation info ennemi\n");
        }
        nouv_ennemi->info_ennemi = info_nouv;
    }
    else
    {
        printf("Erreur d'allocation ennemi\n");
    }
    if (tf->tete == NULL)
    { // Si la liste vide
        tf->tete = nouv_ennemi;
    }
    else
    { // Il existe déjà au moins un ennemi
        ennemi_t *courant;
        courant = tf->tete;
        while (courant->ennemi_suivant != NULL)
        { // ennemi_suivant non NULL
            courant = courant->ennemi_suivant;
        }
        courant->ennemi_suivant = nouv_ennemi;
        courant = courant->ennemi_suivant;
    }
}

void mort_ennemi(ennemis_t *tf, ennemi_t *ennemi_a_tuer)
{
    ennemi_t *prec;
    prec = tf->tete;
    while (prec->ennemi_suivant != ennemi_a_tuer)
    { // On cherche l'ennemi précédent
        prec = prec->ennemi_suivant;
    }
    if (ennemi_a_tuer->ennemi_suivant != NULL)
    { // Il existe un ennemi après celui qu'on tue
        prec->ennemi_suivant = ennemi_a_tuer->ennemi_suivant;
    }
    else
    {
        prec->ennemi_suivant = NULL;
    }
    free(ennemi_a_tuer);
}

ennemis_t *ennemi_toucher(ennemis_t *tf, int tir_x, int tir_y, int tir_w, int tir_h)
{ // Retourne l'ennemi à tuer
}

void afficher_ennemis(ennemis_t *tf, SDL_Texture *texture, SDL_Renderer *renderer)
{
    if (tf->tete != NULL)
    { // S'il existe des ennemis
        ennemi_t *courant;
        courant = tf->tete;
        int x, y, w, h;
        do
        {
            x = courant->info_ennemi->x;
            y = courant->info_ennemi->y;
            w = courant->info_ennemi->w;
            h = courant->info_ennemi->h;
            afficher_texture(texture, renderer, w, h, x, y);
            courant = courant->ennemi_suivant;
        } while (courant->ennemi_suivant != NULL);
        x = courant->info_ennemi->x;
        y = courant->info_ennemi->y;
        w = courant->info_ennemi->w;
        h = courant->info_ennemi->h;
        afficher_texture(texture, renderer, w, h, x, y);
    }
}

void liberation_ennemis(ennemi_t *tf)
{ // Il faudra mettre tf->tete en paramètre
    if (tf->ennemi_suivant != NULL)
    {
        liberation_ennemis(tf->ennemi_suivant);
    }
    free(tf);
}

void nouveau_theta(int *theta)
{ 
    int proba = rand()%101;
    int i=0;
    int thetaActuel=((*theta)/10)+2;
    float sommeProba=matriceTheta[thetaActuel][i]*100;

    while(proba>sommeProba){
        i++;
        sommeProba+=matriceTheta[thetaActuel][i]*100;
    }

    *theta=valeursTheta[i];
}