#include "save.h"

void chargerConfig(char *nom_fichier, int **config, int taille_X, int taille_Y)
{ // On passe taille_X et taille_Y en passage par adresse pour les récupérer.
  // Le fichier contient sur la 1ère ligne: taille_X taille_Y
  // Puis: 11100011011\n
  //       11001101100\n
    FILE *file = fopen(nom_fichier, "r");
    if (file)
    {
        int i, j;
        fscanf(file, "%i %i", &taille_X, &taille_Y);
        for (i = 0; i < taille_X; i++)
        {
            for (j = 0; j < taille_Y; j++)
            {
                fscanf(file, "%d", &config[i][j]);
            }
        }
    }
    fclose(file);
}

void saveConfig(char *nom_fichier, int **config, int taille_X, int taille_Y)
{
    FILE *file = fopen(nom_fichier, "w");
    if (file)
    {
        fprintf(file, "%i %i\n", taille_X, taille_Y);
        int i, j;
        for (i = 0; i < taille_X; i++)
        {
            for (j = 0; j < taille_Y; j++)
            {
                fprintf(file, "%i", config[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}