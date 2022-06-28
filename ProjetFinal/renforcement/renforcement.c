#include "renforcement.h"

// Prend l'état du monde et renvoie l'état de perception s
int perception(ball_t ball,player_t player)
{
    float distance=sqrt(pow(player.x-ball.x,2)+pow(player.y-ball.y,2));
    float angle;
    if (player.y>ball.y) angle=360 -(M_PI/2 + asin((ball.x-player.x)/distance))*180/M_PI;
    else angle=(M_PI/2 + asin((ball.x-player.x)/distance))*180/M_PI;

    if(angle<=22 && angle>337){//droite
        if(distance <= DISTANCE1){
            return RIGHT1;
        }
        else if(distance <DISTANCE2){
            return RIGHT2;
        }else{
            return RIGHT3;
        }
    }else if(angle>22 && angle<67){
        if(distance <= DISTANCE1){
            return UR1;
        }
        else if(distance <DISTANCE2){
            return UR2;
        }else{
            return UR3;
        }
    }else if(angle>=67 && angle<112){
        if(distance <= DISTANCE1){
            return UP1;
        }
        else if(distance <DISTANCE2){
            return UP2;
        }else{
            return UP3;
        }
    }else if(angle>=112 && angle<158){
        if(distance <= DISTANCE1){
            return UL1;
        }
        else if(distance <DISTANCE2){
            return UL2;
        }else{
            return UL3;
        }
    }else if(angle>=158 && angle<202){
        if(distance <= DISTANCE1){
            return LEFT1;
        }
        else if(distance <DISTANCE2){
            return LEFT2;
        }else{
            return LEFT3;
        }
    }else if(angle>=202 && angle<248){
        if(distance <= DISTANCE1){
            return DL1;
        }
        else if(distance <DISTANCE2){
            return DL2;
        }else{
            return DL3;
        }
    }else if(angle>=248 && angle<292){
        if(distance <= DISTANCE1){
            return DOWN1;
        }
        else if(distance <DISTANCE2){
            return DOWN2;
        }else{
            return DOWN3;
        }
    }else if(angle>=292 && angle<=337){
        if(distance <= DISTANCE1){
            return DR1;
        }
        else if(distance <DISTANCE2){
            return DR2;
        }else{
            return DR3;
        }
    }
}

void evolution(ordinateur_t *ordi, int *suiteEtats, int *suiteActions, int *suiteRecompenses, int n)
{ // Prend le monde et une action et modifie l'état du monde
    int i, max, a;
    ordi->QTable[suiteEtats[n - 1]][suiteActions[n - 1]] += XI * (suiteActions[n] - ordi->QTable[suiteActions[n - 1]][suiteEtats[n - 1]]);
    for (i = n - 2; i > 0; i--)
    {
        max = ordi->QTable[suiteEtats[i + 1]][0];
        for (a = 1; a < NBACTIONS; a++)
        {
            if (max < ordi->QTable[i + 1][a])
            {
                max = ordi->QTable[i + 1][a];
            }
            ordi->QTable[suiteEtats[i]][suiteActions[i]] += XI * (suiteRecompenses[i + 1] + GAMMA * max - ordi->QTable[suiteEtats[i]][suiteActions[i]]);
        }
    }
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

int choixAction(ordinateur_t ordi, int s, int T)
{                               // Prend une perception et le monde et renvoie l'action choisie
    int a = 0,avecTir=1;        // Parcours de actions
    if(s>=NBETATDISTANCE1){
        avecTir=0;
    }
    int action = NBACTIONS - avecTir - 1; // Action par défaut
    float Z = 0;      // Somme des énergies
    int E[NBACTIONS-avecTir]; // Energies des actions
    float alpha;      // Réel aléatoire dans [0; 1[
    int cumul = 0;

    for (a = 0; a < NBACTIONS-avecTir; a++)
    {
        E[a] = exp(ordi.QTable[s][a] / T);
        Z += E[a];
    }
    alpha = rand();
    for (a = 0; a < NBACTIONS-avecTir; a++)
    {
        cumul += E[a] / Z;
        if (alpha <= cumul)
        {
            action = a;
            break;
        }
    }
    return action;
}

void renforcement()
{ // Fonction principale
}
