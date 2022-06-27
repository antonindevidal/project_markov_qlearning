#include "renforcement.h"

void perception()
{ // Prend l'état du monde et renvoie l'état de perception s
}

void evolution()
{ // Prend le monde et une action et modifie l'état du monde
}

// récompense lié à l'avancement de l'objectif
int recompense(ball_t precBall, ball_t ball, player_t precPlayer, player_t player, int isGoal)
{ 
    int ecart,ecartPrec,ecartNouv;
    if(isGoal){
        return But;
    }
    //La balle a bougée
    else if(precBall.x != ball.x){
        ecart=sqrt(pow(precBall.x+ball.x,2)+pow(precBall.y+ball.y,2));
        if(ecart>100){
            if(precBall.x < ball.x){
                if(player.equipe==EQUIPEGAUCHE) return balleBeacoupRapprocheBut;
                else return balleEloigneBeaucoupbut;
            }
            else{
                if(player.equipe==EQUIPEDROITE) return balleBeacoupRapprocheBut;
                else return balleEloigneBeaucoupbut;
            }
        }
        else{
            if(precBall.x < ball.x){
                if(player.equipe==EQUIPEGAUCHE) return balleRapprocheBut;
                else return balleEloigneBut;
            }
            else{
                if(player.equipe==EQUIPEDROITE) return balleRapprocheBut;
                else return balleEloigneBut;
            }
        }
    }
    else{
        ecartPrec=sqrt(pow(precBall.x+precPlayer.x,2)+pow(precBall.y+precPlayer.y,2));
        ecartNouv=sqrt(pow(ball.x+player.x,2)+pow(ball.y+player.y,2));
        if(ecartNouv<ecartPrec)return seRapprocheDeLaBalle;
        else return sEloigneDeLaBalle;
    }
}

void enumerationActions()
{ // Prend le monde et renvoie une énumération des actions possibles
}

int choixAction(ordinateur_t *ordi, int perception)
{ // Prend une perception et le monde et renvoie l'action choisie
    int i = 0;
    float alpha;
    float sommeCummule = ordi->QTable[perception][0];
    float sommeLigne = 0;
    for (i = 0; i < NBACTIONS; i++)
    {
        sommeLigne += ordi->QTable[perception][i];
    }
    //alpha = rand() % sommeLigne;
    i = 0;
    while (alpha > sommeCummule)
    {
        i++;
        sommeCummule += ordi->QTable[perception][i];
    }
    return i;
}

void renforcement()
{ // Fonction principale
}
