#include 'cycle.h'

//mode=0 mode normal
//mode=1 mode thorique
int nbVoisin(int i, int j, int tailleX, int tailleY, int **cour,int mode){
    int nbVoisin=0;
    if(k!=tailleX)
    for(int k=(i-1)%tailleX;k<=i+1;k++){
        for(int r=(j-1)%tailleY;r<=j+1;r++){
            if(k!=i && r!=j){
                if(cour[k][r]){
                    nbVoisin++;
                }
            }
        }
    }

    if(!mode){
    int haut=i>0;
    int bas=i<tailleY;
    int gauche=j>0;
    int droite=j<tailleX;

    if(haut)nbVoisin+=cour[i-1][j];
    if(bas) nbVoisin+=cour[i+1][j];
    if(gauche)nbVoisin+=cour[i][j-j];
    if(droite)nbVoisin+=cour[i][j+1];
    if(haut && gauche)nbVoisin+=cour[i-1][j-1];
    if(haut && droite)nbVoisin+=cour[i-1][j+1];
    if(bas && gauche)nbVoisin+=cour[i+1][j-1];
    if(bas && droite)nbVoisin+=cour[i+1][j+1];
    
    }
    //Mode thorique
    else{
        nbVoisin+=cour[(i-1)%tailleY][(j-1)%tailleX];//haut
        nbVoisin+=cour[(i-1)%tailleY][j];
        nbVoisin+=cour[(i-1)%tailleY][(j+1)%tailleX];

        nbVoisin+=cour[(i+1)%tailleY][(j-1)%tailleX];//bas
        nbVoisin+=cour[(i+1)%tailleY][j];
        nbVoisin+=cour[(i+1)%tailleY][(j+1)%tailleX];

        nbVoisin+=cour[i][(j-1)%tailleX];//gauche
        nbVoisin+=cour[i][(j+1)%tailleX];//droite

    }
    return nbVoisin;
}

//mode=0 mode normal
//mode=1 mode thorique
void cycle(int** nouv, int** anc,int mode){

}