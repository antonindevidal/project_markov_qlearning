#include "ennemis.h"

void deplacement(int *x, int *y, float theta, float vitesseX, float vitesseY) {
    /* Calcul la nouvelle position de l'ennemis */
    *x = *x + cos(theta *  M_PI / 180) * vitesseX;
    *y = *y + sin(theta * M_PI / 180) * vitesseY;
}

void nouveau_theta(float *theta) {
    /* Calcul le nouveau theta à l'aide des chaînes de Markov */
}