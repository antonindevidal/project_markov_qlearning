#ifndef __SAVE_H__
#define __SAVE_H__
#include <stdio.h>

/* Déclaration des prototypes */
void chargerConfig(char *nom_fichier, int **config, int taille_X, int taille_Y);
void saveConfig(char *nom_fichier, int **config, int taille_X, int taille_Y);

#endif
