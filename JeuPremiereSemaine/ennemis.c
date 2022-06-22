#include "ennemis.h"

void deplacement(int *x, int *y, float theta, float vitesseX, float vitesseY)
{
    /* Calcul la nouvelle position de l'ennemis */
    *x = *x + cos(theta * M_PI / 180) * vitesseX;
    *y = *y + sin(theta * M_PI / 180) * vitesseY;
}

void init_ennemi(ennemis_t * tf)
{
    
}

void ajout_ennemi(ennemis_t * tf, int x, int y, int w, int h)
{
}

void mort_ennemi(ennemis_t * tf, ennemis_t * ennemi_a_tuer)
{
}

ennemis_t * ennemi_toucher(ennemis_t * tf, int tir_x, int tir_y, int tir_w, int tir_h) 
{ //Retourne l'ennemi à tuer

}

void afficher_ennemis(ennemis_t * tf)
{
}

void liberation_ennemis(ennemis_t * tf)
{
}

void nouveau_theta(float *theta)
{
    /* Calcul le nouveau theta à l'aide des chaînes de Markov */
}