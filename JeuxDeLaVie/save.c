#include "save.c"

void chargerConfig(char *nom_fichier, int **config, int taille_X, int taille_Y)
{
    FILE *file = fopen(nom_fichier, "r");
    if (file)
    {
        int i, j;
        fir (i=0; i<taille_X; i++) {
            fgets(ligne, taille_Y, file);
        }
    }
    fclose(file);
}

void saveConfig(char *nom_fichier, int **config, int taille_X, int taille_Y)
{
    FILE *file = fopen(nom_fic, "w");
    if (file)
    {
        int i, j;
        for (i=0; i<taille_X; i++) {
            for (j=0; j<taille_Y; j++) {
                fprintf(file, "%i", config[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}