#include "renforcement.h"


int distanceAdversaire(ball_t ball, player_t player)
{
    float distance = sqrt(pow(player.x - ball.x, 2) + pow(player.y - ball.y, 2));
    if (distance <= DISTANCE1)
    {
        return 1;
    }
    else if (distance < DISTANCE2)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}


// Prend l'état du monde et renvoie l'état de perception s
int perception(ball_t ball, player_t player, player_t player2)
{
    int etat;
    float distance = sqrt(pow(player.x - ball.x, 2) + pow(player.y - ball.y, 2));
    float angle;
    if (player.y > ball.y)
        angle = 360 - (M_PI / 2 + asin((ball.x - player.x) / distance)) * 180 / M_PI;
    else
        angle = (M_PI / 2 + asin((ball.x - player.x) / distance)) * 180 / M_PI;

    if (angle <= 22 && angle > 337)
    { // droite
        if (distance <= DISTANCE1)
        {
            etat= RIGHT11;
        }
        else if (distance < DISTANCE2)
        {
            etat= RIGHT21;
        }
        else
        {
            etat= RIGHT31;
        }
    }
    else if (angle > 22 && angle < 67)
    {
        if (distance <= DISTANCE1)
        {
            etat= UR11;
        }
        else if (distance < DISTANCE2)
        {
            etat= UR21;
        }
        else
        {
            etat= UR31;
        }
    }
    else if (angle >= 67 && angle < 112)
    {
        if (distance <= DISTANCE1)
        {
            etat= UP11;
        }
        else if (distance < DISTANCE2)
        {
            etat= UP21;
        }
        else
        {
            etat= UP31;
        }
    }
    else if (angle >= 112 && angle < 158)
    {
        if (distance <= DISTANCE1)
        {
            etat= UL11;
        }
        else if (distance < DISTANCE2)
        {
            etat= UL21;
        }
        else
        {
            etat= UL31;
        }
    }
    else if (angle >= 158 && angle < 202)
    {
        if (distance <= DISTANCE1)
        {
            etat= LEFT11;
        }
        else if (distance < DISTANCE2)
        {
            etat= LEFT21;
        }
        else
        {
            etat= LEFT31;
        }
    }
    else if (angle >= 202 && angle < 248)
    {
        if (distance <= DISTANCE1)
        {
            etat= DL11;
        }
        else if (distance < DISTANCE2)
        {
            etat= DL21;
        }
        else
        {
            etat= DL31;
        }
    }
    else if (angle >= 248 && angle < 292)
    {
        if (distance <= DISTANCE1)
        {
            etat= DOWN11;
        }
        else if (distance < DISTANCE2)
        {
            etat= DOWN21;
        }
        else
        {
            etat= DOWN31;
        }
    }
    else if (angle >= 292 && angle <= 337)
    {
        if (distance <= DISTANCE1)
        {
            etat= DR11;
        }
        else if (distance < DISTANCE2)
        {
            etat= DR21;
        }
        else
        {
            etat= DR31;
        }
    }
    if(distanceAdversaire(ball,player2)!=1){
        etat++;
    }
    return etat;
}

void evolution(ordinateur_t *ordi, int *suiteEtats, int *suiteActions, int *suiteRecompenses, int n)
{ // Prend le monde et une action et modifie l'état du monde
    int i, max, a;
    ordi->QTable[suiteEtats[n - 1]][suiteActions[n - 1]] += XI * (suiteActions[n] - ordi->QTable[suiteActions[n - 1]][suiteEtats[n - 1]]);
    for (i = n - 2; i >= 0; i--)
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
int recompense(ball_t precBall, ball_t ball, player_t precPlayer, player_t player, int isGoal, enum EQUIPE equipeBut)
{
    int ecart, ecartPrec, ecartNouv;
    if (isGoal && equipeBut==player.equipe)
    {
        return But;
    }
    // La balle a bougé
    else if (precBall.x != ball.x)
    {
        ecart = sqrt(pow(precBall.x + ball.x, 2) + pow(precBall.y + ball.y, 2));
        if (ecart > 100)
        {
            if (precBall.x < ball.x)
            {
                if (player.equipe == EQUIPEGAUCHE)
                    return balleBeacoupRapprocheBut;
                else
                    return balleEloigneBeaucoupbut;
            }
            else
            {
                if (player.equipe == EQUIPEDROITE)
                    return balleBeacoupRapprocheBut;
                else
                    return balleEloigneBeaucoupbut;
            }
        }
        else
        {
            if (precBall.x < ball.x)
            {
                if (player.equipe == EQUIPEGAUCHE)
                    return balleRapprocheBut;
                else
                    return balleEloigneBut;
            }
            else
            {
                if (player.equipe == EQUIPEDROITE)
                    return balleRapprocheBut;
                else
                    return balleEloigneBut;
            }
        }
    }
    else
    {
        ecartPrec = sqrt(pow(precBall.x + precPlayer.x, 2) + pow(precBall.y + precPlayer.y, 2));
        ecartNouv = sqrt(pow(ball.x + player.x, 2) + pow(ball.y + player.y, 2));
        if (ecartNouv < ecartPrec)
            return seRapprocheDeLaBalle;
        else
            return sEloigneDeLaBalle;
    }
}

int choixAction(ordinateur_t ordi, int s, int T)
{                           // Prend une perception et le monde et renvoie l'action choisie
    int a = 0, avecTir = 1; // Parcours de actions
    if (s >= NBETATDISTANCE1)
    {
        avecTir = 0;
    }
    int action = NBACTIONS - avecTir - 1; // Action par défaut
    float Z = 0;                          // Somme des énergies
    int E[NBACTIONS - avecTir];           // Energies des actions
    float alpha;                          // Réel aléatoire dans [0; 1[
    int cumul = 0;

    for (a = 0; a < NBACTIONS - avecTir; a++)
    {
        E[a] = exp(ordi.QTable[s][a] / T);
        Z += E[a];
    }
    alpha = rand();
    for (a = 0; a < NBACTIONS - avecTir; a++)
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
/*
void initPartie(ordinateur_t *ordi1,ordinateur_t *ordi2,ball_t **ball,ball_t **precball){
    *ball=creationBall();
    *precball=creationBall();
    resetEmplacement(ordi1);
    resetEmplacement(ordi2);
}


void renforcement(ordinateur_t *ordi1, ordinateur_t *ordi2)
{ // Fonction principale

    int isGoal=1, equipeBut,nbActionPourReset=0;
    int epoque, pas, T;
    int s1[NBEPOCH], a1[NBEPOCH - 1], r1[NBEPOCH]; // Liste états, actions et récompenses pour joueur 1
    int s2[NBEPOCH], a2[NBEPOCH - 1], r2[NBEPOCH]; // Liste états, actions et récompenses pour joueur 2
    

    T = 0.9;
    
    player_t prec1,prec2;
    ball_t* ball;
    ball_t* precball;

    for (epoque = 0; epoque < MAXEPOCH; epoque++)
    {
        // Reset le monde
        if(isGoal || nbActionPourReset>=5){
            isGoal=0;
            nbActionPourReset=0;
            initPartie(ordi1,ordi2,&ball,&precball);
            copie(prec1,ordi1->player);
            copie(prec2,ordi2->player);
        }
        
        for (pas = 0; pas < NBEPOCH)
        {   
            //1 itération du jeu(avec isGoal)

            r1[pas] = recompense(precBall, ball, prec1, ordi1->player, isGoal, equipeBut); // Récompense joueur1
            r2[pas] = recompense(precBall, ball, prec2, ordi2->player, isGoal, equipeBut); // Récompense joueur2
            s1[pas] = perception(ball, ordi1->player);                               // Etat actuel joueur1
            s2[pas] = perception(ball, ordi2->player);                               // Etat actuel joueur2

            // Si c'est un apprentissage de qualité d'états : mettre à jour les successeurs de l'état perçu
            a1[pas] = choixAction(ordi1, s1[pas], T);
            a2[pas] = choixAction(ordi2, s2[pas], T);

            // Appliquer l'action choisie au monde
            if (isGoal) // Si l'état atteint est terminal : break => but
                break;
        }
        nbActionPourReset++;
        evolution(ordi1, s1, a1, r1, NBEPOCH);
        evolution(ordi2, s2, a2, r2, NBEPOCH);
    }
}*/

void resetEmplacement(ordinateur_t *ordi) { 
    int rx=rand()%3; rx--; //rx = -1, 0 ou 1
    int ry=rand()%3; ry--;
    ordi->player.x = ordi->player.x + 20*rx;
    ordi->player.y = ordi->player.y + 20*ry;
}

void saveQTable(char *nom_fichier, float **QTable) {
    FILE *file = fopen(nom_fichier, "w");
    if (file)
    {
        int i, j;
        for (i=0; i<NBETATS; i++) {
            for (j=0; j<NBACTIONS; j++) {
                fprintf(file, "%f", QTable[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

void chargerQTable(char *nom_fichier, float **Qtable) 
{
    FILE *file = fopen(nom_fichier, "r");
    if (file)
    {
        int i, j;
        for (i=0; i<NBETATS; i++) {
            for (j=0; j<NBACTIONS; j++) {
                fscanf(file, "%f", &Qtable[i][j]);
            }
        }
    }
    fclose(file);
}

void copie(player_t *prec, player_t *ordi) {
    prec->dir = ordi->dir;
    prec->equipe = ordi->equipe;
    prec->h = ordi->h;
    prec->w = ordi->w;
    prec->x = ordi->x;
    prec->y = ordi->y;
}
