#include "cycle.h"
#include "data.h"

// mode=0 mode normal
// mode=1 mode thorique
int nbVoisin(int i, int j, int tailleX, int tailleY, int **cour, int mode)
{
    int nbVoisin = 0;

    if (!mode)
    {
        int haut = i > 0;
        int bas = i < tailleY - 1;
        int gauche = j > 0;
        int droite = j < tailleX - 1;

        if (haut)
            nbVoisin += cour[i - 1][j];
        if (bas)
            nbVoisin += cour[i + 1][j];
        if (gauche)
            nbVoisin += cour[i][j - 1];
        if (droite)
            nbVoisin += cour[i][j + 1];
        if (haut && gauche)
            nbVoisin += cour[i - 1][j - 1];
        if (haut && droite)
            nbVoisin += cour[i - 1][j + 1];
        if (bas && gauche)
            nbVoisin += cour[i + 1][j - 1];
        if (bas && droite)
            nbVoisin += cour[i + 1][j + 1];
    }
    // Mode thorique
    else
    {
        nbVoisin += cour[(tailleY + i - 1) % tailleY][(tailleX + j - 1) % tailleX]; // haut
        nbVoisin += cour[(tailleY + i - 1) % tailleY][j];
        nbVoisin += cour[(tailleY + i - 1) % tailleY][(j + 1) % tailleX];

        nbVoisin += cour[(i + 1) % tailleY][(tailleX + j - 1) % tailleX]; // bas
        nbVoisin += cour[(i + 1) % tailleY][j];
        nbVoisin += cour[(i + 1) % tailleY][(j + 1) % tailleX];

        nbVoisin += cour[i][(tailleX + j - 1) % tailleX]; // gauche
        nbVoisin += cour[i][(j + 1) % tailleX];           // droite
    }
    return nbVoisin;
}

// mode=0 mode normal
// mode=1 mode thorique
void cycle(int **nouv, int **anc, int tailleX, int tailleY, int mode)
{

    int nb;
    for (int i = 0; i < tailleY; i++)
    {
        for (int j = 0; j < tailleX; j++)
        {
            nb = nbVoisin(i, j, tailleX, tailleY, anc, mode);
            // si vivant de base
            if (anc[i][j])
            {
                nouv[i][j] = survie[nb];
            }
            // si mort de base
            else
            {
                nouv[i][j] = naissance[nb];
            }
        }
    }
}

void detection_etat_stable(int **anc, int **nouv, int taille_x, int taille_y)
{
    int i = 0, j = 0;
    int stable = 1;
    while ((i < taille_y) && stable)
    {
        j = 0;
        while ((j < taille_x) && stable)
        {
            if (anc[i][j] != nouv[i][j])
            {
                stable = 0;
            }
            j++;
        }
        i++;
    }
    if (stable)
        printf("Etat stable\n");
}