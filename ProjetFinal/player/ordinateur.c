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
    if (ordi == NULL) exit(1);
    ordi->player = createPlayer(equipe);
    ordi->QTable = (float **)malloc(NBETATS * sizeof(float *));
    if (ordi->QTable == NULL) exit(1);
    for (int i = 0; i < NBETATS; i++)
    { 
        ordi->QTable[i]=(float*)malloc(NBACTIONS*sizeof(float));
        if(ordi->QTable[i] == NULL)
        {
            exit(0);
        }
        //memset(ordi->QTable,0,NBACTIONS);
        for (int j = 0; j < NBACTIONS; j++)
        {
            ordi->QTable[i][j] = (float)0.0;
        }
    }
    //afficherQTable(ordi->QTable,NBETATS,NBACTIONS);
    
    return ordi;
}

void libererOrdi(ordinateur_t *ordi)
{
    int i;
    for (i = 0; i < NBETATS; i++)
    {
        free(ordi->QTable[i]);
    }
    free(ordi->QTable);
    free(ordi->player);
    free(ordi);
}

void afficherQTable(float **tab, int n,int m) {
    for(int i=0;i<n;i++){
        printf("\n");
        for(int j=0; j<m;j++){
            printf("%f ",tab[i][j]);
        }
    }
}
// void afficherQTable(ordinateur_t *ordi)
// {
//     int i, j;
//     for (i = 0; i < NBETATS; i++)
//     {
//         for (j = 0; j < NBACTIONS; j++)
//         {
//             printf("%.2f ", ordi->QTable[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }