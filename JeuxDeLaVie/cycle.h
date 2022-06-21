#ifndef __CYCLE_H__
#define __CYCLE_H__
#include <stdio.h>

/* Déclaration des prototypes */
int detection_etat_stable(int **anc, int **nouv, int taille_x, int taille_y);

int nbVoisin(int i, int j, int tailleX, int tailleY, int **cour,int mode);
void cycle(int** nouv, int** anc, int tailleX, int tailleY,int mode);

#endif
