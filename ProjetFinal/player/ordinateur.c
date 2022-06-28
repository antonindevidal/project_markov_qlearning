#include "ordinateur.h"

void initQTableOrdi(ordinateur_t *ordi)
{
    int i, j;

    for (i = 0; i < NBETATS; i++)
    {
        for (j = 0; j < NBACTIONS; j++)
        {
            ordi->QTable[i][j] = 0;
        }
    }
}

ordinateur_t *creerOrdi(enum EQUIPE equipe)
{
    ordinateur_t *ordi;
    ordi = (ordinateur_t *)malloc(sizeof(ordinateur_t));
    if (ordi != NULL)
    {
        ordi->player = createPlayer(equipe);
        //ordi->QTable = (float**)malloc(NBETATS*sizeof(float *));
        initQTableOrdi(ordi);
    }
    return ordi;
}

