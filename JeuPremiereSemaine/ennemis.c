#include "ennemis.h"

// int valeursTheta[TAILLE_MARKOV] = {-300, -150, 0, 150, 300};
// float matriceTheta[TAILLE_MARKOV][TAILLE_MARKOV] = {
//      //      -300  -150   0   +120 +300
//      /*-300*/ {0, 0, 0, 0, 1},
//      /*-150*/ {1, 0, 0, 0, 0},
//      /*  0 */ {0, 1, 0, 0, 0},
//      /*+150*/ {0, 0, 0, 1, 0},
//      /*+300*/ {0, 0, 1, 0, 0}
// };
// float matriceTheta[TAILLE_MARKOV][TAILLE_MARKOV] = {
//      //      -300  -150   0   +120 +300
//      /*-300*/ {0.3, 0.03, 0, 0.02, 0.65},
//      /*-150*/ {0.65, 0.3, 0.03, 0, 0.02},
//      /*  0 */ {0.02, 0.65, 0.3, 0.03, 0},
//      /*+150*/ {0, 0.02, 0.65, 0.3, 0.03},
//      /*+300*/ {0.03, 0, 0.02, 0.65, 0.3}
// };

// int valeursTheta[TAILLE_MARKOV] = {-350, -300, -250, -200, -150, -100, -50, 0, 50, 100, 150, 200, 250, 300, 350};
// float matriceTheta[TAILLE_MARKOV][TAILLE_MARKOV] = {
//     {0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0},
// {0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0},
// {0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0},
// {0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0},
// {0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0},
// {0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0},
// {0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03},
// {0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05},
// {0.2, 0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1},
// {0.5, 0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2},
// {0.05, 0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5},
// {0.05, 0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05},
// {0.02, 0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05},
// {0, 0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02},
// {0, 0, 0, 0, 0, 0, 0.03, 0.05, 0.1, 0.2, 0.5, 0.05, 0.05, 0.02, 0}
// };

int valeursTheta[TAILLE_MARKOV] = {-20, -10, 0, 10, 20};
 float matriceTheta[5][5] = {
    //        -20  -10   0   +10  +20
    /*-20*/ {0.6, 0.3, 0.1, 0.0, 0.0},
    /*-10*/ {0.3, 0.6, 0.1, 0.0, 0.0},
    /*  0*/ {0.3, 0.1, 0.2, 0.1, 0.3},
    /*+10*/ {0.0, 0.0, 0.1, 0.6, 0.3},
    /*+20*/ {0.0, 0.0, 0.1, 0.3, 0.6}};

// test beaucoup de tours sur eux même
//  float matriceTheta[5][5] = {
//      //        -20  -10   0   +10  +20
//      /*-20*/ {0.7, 0.25, 0.05, 0.0, 0.0},
//      /*-10*/ {0.3, 0.6, 0.1, 0.0, 0.0},
//      /*  0*/ {0.05, 0.15, 0.6, 0.15, 0.05},
//      /*+10*/ {0.0, 0.0, 0.1, 0.6, 0.3},
//      /*+20*/ {0.0, 0.0, 0.05, 0.25, 0.7}};

// //Test avec compensation de theta
// float matriceTheta[5][5] = {
//     //        -20  -10   0   +10  +20
//     /*-20*/ {0.3, 0.05, 0.2, 0.25, 0.2},
//     /*-10*/ {0.3, 0.1, 0.2, 0.3, 0.1},
//     /*  0*/ {0.05, 0.15, 0.6, 0.15, 0.05},
//     /*+10*/ {0.1, 0.3, 0.2, 0.1, 0.3},
//     /*+20*/ {0.2, 0.25, 0.2, 0.05, 0.3}};

void deplacementEnnemi(int *x, int *y, int *theta, float vitesseX, float vitesseY)
{
    /* Calcul la nouvelle position de l'ennemis */
    //    if(theta<=60 && theta>=-60)
    //        vitesseX=vitesseX+2;
    if (*x > WINDOWW)
    {
        *theta = 0;
    }
    else if (*x < 0)
    {
        *theta = 180;
    }
    else if (*y < 0)
    {
        *theta = 40;
    }
    else if (*y > WINDOWH)
    {
        *theta = -40;
    }
    *x = *x + cos(*theta * M_PI / 180 + M_PI) * vitesseX;
    *y = *y - sin(*theta * M_PI / 180 + M_PI) * vitesseY;
}

void deplacementEnnemis(listEnnemis_t *tf)
{
    if (tf != NULL)
    { // S'il existe des ennemis
        ennemi_t *courant;
        courant = *tf;
        int vitesseX, vitesseY, theta;
        do
        {
            vitesseX = courant->infoEnnemi->vitesseX;
            vitesseY = courant->infoEnnemi->vitesseY;
            nouveauTheta(&(courant->infoEnnemi->theta));
            courant->infoEnnemi->sommeTheta += courant->infoEnnemi->theta;

            // theta = courant->infoEnnemi->sommeTheta;
            deplacementEnnemi(&courant->infoEnnemi->x, &courant->infoEnnemi->y, &courant->infoEnnemi->sommeTheta, vitesseX, vitesseY);
            courant = courant->ennemiSuivant;
        } while (courant->ennemiSuivant != NULL);
        vitesseX = courant->infoEnnemi->vitesseX;
        vitesseY = courant->infoEnnemi->vitesseY;
        nouveauTheta(&(courant->infoEnnemi->theta));
        courant->infoEnnemi->sommeTheta += courant->infoEnnemi->theta;
        // theta = courant->infoEnnemi->sommeTheta;
        deplacementEnnemi(&courant->infoEnnemi->x, &courant->infoEnnemi->y, &courant->infoEnnemi->sommeTheta, vitesseX, vitesseY);
    }
}

void initEnnemi(listEnnemis_t *tf)
{
    *tf = NULL;
}

void ajoutEnnemi(listEnnemis_t *tf, int x, int y, int w, int h, int vitesseX, int vitesseY)
{
    ennemi_t *nouvEnnemi;
    nouvEnnemi = (ennemi_t *)malloc(sizeof(ennemi_t));
    if (nouvEnnemi != NULL)
    { // Allocation Ok
        nouvEnnemi->ennemiSuivant = NULL;
        infoEnnemi_t *infoNouv;
        infoNouv = (infoEnnemi_t *)malloc(sizeof(infoEnnemi_t));
        if (infoNouv != NULL)
        { // Allocation Ok
            infoNouv->x = x;
            infoNouv->y = y;
            infoNouv->w = w;
            infoNouv->h = h;
            infoNouv->vitesseX = vitesseX;
            infoNouv->vitesseY = vitesseY;
            infoNouv->theta = 0;      // On suppose que l'ennemi va tout droit au départ;
            infoNouv->sommeTheta = 0; // On suppose que l'ennemi va tout droit au départ;
        }
        else
        {
            printf("Erreur d'allocation info ennemi\n");
        }
        nouvEnnemi->infoEnnemi = infoNouv;
    }
    else
    {
        printf("Erreur d'allocation ennemi\n");
    }
    if (*tf == NULL)
    { // Si la liste vide
        *tf = nouvEnnemi;
    }
    else
    { // Il existe déjà au moins un ennemi
        ennemi_t *courant;
        courant = *tf;
        while (courant->ennemiSuivant != NULL)
        { // ennemiSuivant non NULL
            courant = courant->ennemiSuivant;
        }
        courant->ennemiSuivant = nouvEnnemi;
        courant = courant->ennemiSuivant;
    }
}

void mortEnnemi(listEnnemis_t *tf, ennemi_t *ennemiATuer)
{
    ennemi_t *prec;
    prec = *tf;
    while (prec->ennemiSuivant != ennemiATuer)
    { // On cherche l'ennemi précédent
        prec = prec->ennemiSuivant;
    }
    if (ennemiATuer->ennemiSuivant != NULL)
    { // Il existe un ennemi après celui qu'on tue
        prec->ennemiSuivant = ennemiATuer->ennemiSuivant;
    }
    else
    {
        prec->ennemiSuivant = NULL;
    }
    free(ennemiATuer);
}

ennemi_t *ennemiToucher(listEnnemis_t tf, int tirX, int tirY, int tirW, int tirH)
{ // Retourne l'ennemi à tuer
}

void afficherEnnemis(listEnnemis_t tf, SDL_Texture *texture, SDL_Renderer *renderer)
{
    if (tf != NULL)
    { // S'il existe des ennemis
        ennemi_t *courant;
        courant = tf;
        int x, y, w, h;
        do
        {
            x = courant->infoEnnemi->x;
            y = courant->infoEnnemi->y;
            w = courant->infoEnnemi->w;
            h = courant->infoEnnemi->h;
            afficherTexture(texture, renderer, w, h, x, y);
            courant = courant->ennemiSuivant;
        } while (courant->ennemiSuivant != NULL);
        x = courant->infoEnnemi->x;
        y = courant->infoEnnemi->y;
        w = courant->infoEnnemi->w;
        h = courant->infoEnnemi->h;
        afficherTexture(texture, renderer, w, h, x, y);
    }
}

void liberationEnnemis(listEnnemis_t tf)
{ // Il faudra mettre tf en paramètre
    if (tf->ennemiSuivant != NULL)
    {
        liberationEnnemis(tf->ennemiSuivant);
    }
    free(tf);
}

void nouveauTheta(int *theta)
{
    int proba = rand() % 101;
    int i = 0, indTheta = 0;

    while (valeursTheta[indTheta] != *theta)
    {
        indTheta++;
    }

    float sommeProba = matriceTheta[indTheta][i] * 100;
    while ((proba > sommeProba))
    {
        i++;
        sommeProba += matriceTheta[indTheta][i] * 100;
    }
    *theta = valeursTheta[i];
}