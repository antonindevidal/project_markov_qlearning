#include "ordinateur.h"

void initQTableOrdi(ordinateur_t *ordi)
{
    int i, j;
    ordi->QTable=(float**)malloc(NBETATS*sizeof(float *));

    for (i = 0; i < NBETATS; i++)
    { ordi->QTable[i]=(float*)malloc(NBACTIONS*sizeof(float));
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
    if (ordi == NULL)
    {
        exit(1);
        //ordi->QTable = (float**)malloc(NBETATS*sizeof(float *));
    }
    ordi->player = createPlayer(equipe);
    ordi->QTable=(float**)malloc(NBETATS*sizeof(float *));
    if(ordi->QTable == NULL)
    {   
        exit(0);
    }
    for (int i = 0; i < NBETATS; i++)
    { 
        ordi->QTable[i]=(float*)malloc(NBACTIONS*sizeof(float));
        if(ordi->QTable[i] == NULL)
        {
            exit(0);
        }
        memset(ordi->QTable,0,NBACTIONS);
        // for (int j = 0; j < NBACTIONS; j++)
        // {
        //     ordi->QTable[i][j] = (float)0.0;
        // }
    }
    
    return ordi;
}

