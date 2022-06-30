#include "renforcement.h"

int distanceAdversaire(ball_t ball, player_t player)
{
    float distance = sqrt(pow(player.x - ball.x, 2) + pow(player.y - ball.y, 2));
    if (distance <= DISTANCE1)
    {
        return 1;
    }
    else if (distance <= DISTANCE2)
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
    int etat = RIGHT11;
    float distance = sqrt(pow(player.x - ball.x, 2) + pow(player.y - ball.y, 2));
    float angle = 0;
    if (player.y > ball.y)
        angle = 360 - (M_PI / 2 + asin((ball.x - player.x) / distance)) * 180 / M_PI;
    else
        angle = (M_PI / 2 + asin((ball.x - player.x) / distance)) * 180 / M_PI;

    if (angle <= 22 || angle > 337)
    { // droite
        if (distance <= DISTANCE1)
        {
            etat = RIGHT11;
        }
        else if (distance <= DISTANCE2)
        {
            etat = RIGHT21;
        }
        else
        {
            etat = RIGHT31;
        }
    }
    else if (angle > 22 && angle < 67)
    {
        if (distance <= DISTANCE1)
        {
            etat = UR11;
        }
        else if (distance < DISTANCE2)
        {
            etat = UR21;
        }
        else
        {
            etat = UR31;
        }
    }
    else if (angle >= 67 && angle < 112)
    {
        if (distance <= DISTANCE1)
        {
            etat = UP11;
        }
        else if (distance < DISTANCE2)
        {
            etat = UP21;
        }
        else
        {
            etat = UP31;
        }
    }
    else if (angle >= 112 && angle < 158)
    {
        if (distance <= DISTANCE1)
        {
            etat = UL11;
        }
        else if (distance < DISTANCE2)
        {
            etat = UL21;
        }
        else
        {
            etat = UL31;
        }
    }
    else if (angle >= 158 && angle < 202)
    {
        if (distance <= DISTANCE1)
        {
            etat = LEFT11;
        }
        else if (distance < DISTANCE2)
        {
            etat = LEFT21;
        }
        else
        {
            etat = LEFT31;
        }
    }
    else if (angle >= 202 && angle < 248)
    {
        if (distance <= DISTANCE1)
        {
            etat = DL11;
        }
        else if (distance < DISTANCE2)
        {
            etat = DL21;
        }
        else
        {
            etat = DL31;
        }
    }
    else if (angle >= 248 && angle < 292)
    {
        if (distance <= DISTANCE1)
        {
            etat = DOWN11;
        }
        else if (distance < DISTANCE2)
        {
            etat = DOWN21;
        }
        else
        {
            etat = DOWN31;
        }
    }
    else // if (angle >= 292 && angle <= 337)
    {
        if (distance <= DISTANCE1)
        {
            etat = DR11;
        }
        else if (distance < DISTANCE2)
        {
            etat = DR21;
        }
        else
        {
            etat = DR31;
        }
    }
    if(distanceAdversaire(ball,player2) !=1){
        etat++;
    }

    return etat;
}

float maxQTable(ordinateur_t ordi, int indEtat, int *s)
{
    float maxi;
    int r, j;
    r = rand() % NBACTIONS;
    maxi = ordi.QTable[s[indEtat]][r];
    for (j = 0; j < NBACTIONS; j++)
    {
        if ((j != r) && (maxi < ordi.QTable[s[indEtat]][j]))
        {
            maxi = ordi.QTable[s[indEtat]][j];
        }
    }
    return maxi;
}

void evolution(ordinateur_t *ordi, int *s, int *a, int *r, int n)
{ // Prend le monde et une action et modifie l'état du monde
    float max;
    int i;
    ordi->QTable[s[n - 1]][a[n - 1]] += XI * (r[n] - ordi->QTable[s[n - 1]][a[n - 1]]);
    for (i = n - 2; i >= 0; i--)
    {
        max = maxQTable(*ordi, i + 1, s);
        ordi->QTable[s[i]][a[i]] += XI * (r[i + 1] + GAMMA * max - ordi->QTable[s[i]][a[i]]);
    }
}

// récompense lié à l'avancement de l'objectif
int recompense(ball_t precBall, ball_t ball, player_t precPlayer, player_t player, int isGoal, enum EQUIPE equipeBut)
{
    int ecart, ecartPrec, ecartNouv;
    ecart = sqrt(pow(precBall.x - ball.x, 2) + pow(precBall.y - ball.y, 2));

    if (isGoal && equipeBut == player.equipe)
    {
        return But;
    }
    // La balle a bougé
    else if (ecart != 0)
    {
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
        ecartPrec = sqrt(pow(precBall.x - precPlayer.x, 2) + pow(precBall.y - precPlayer.y, 2));
        ecartNouv = sqrt(pow(ball.x - player.x, 2) + pow(ball.y - player.y, 2));
        if (ecartNouv < ecartPrec)
            return seRapprocheDeLaBalle;
        else if (ecartNouv > ecartPrec)
            return sEloigneDeLaBalle;
        else
            return rateLeTir;
    }
}

int choixAction(ordinateur_t *ordi, int s, float T)
{                    // Prend une perception et le monde et renvoie l'action choisie
    int avecTir = 1; // Parcours de actions
    if (s >= NBETATDISTANCE1)
    {
        avecTir = 0;
    }
    int action = NBACTIONS + avecTir - 2; // Action par défaut
    float Z = 0;                          // Somme des énergies
    float E[NBACTIONS - 1 + avecTir];     // Energies des actions
    float alpha = 0;                      // Réel aléatoire dans [0; 1[
    float cumul = 0;

    for (int a = 0; a < NBACTIONS - 1 + avecTir; a++)
    {
        float g = ((ordi->QTable)[s][a]) / T;
        E[a] = exp(g);
        Z += E[a];
    }
    alpha = (rand() % 100) / 100.0;
    for (int a = 0; a < NBACTIONS + avecTir - 1; a++)
    {
        cumul += E[a] / Z;
        if (alpha <= cumul)
        {
            action = a;
            break;
        }
    }
    //printf("action: %d\n", action);
    return action;
}

// int choixAction(ordinateur_t *ordi, int s, float T)
// {               // Prend une perception et le monde et renvoie l'action choisie
//     float max=-2;
//     int action=0;
//     for(int i=0;i<9;i++){
//         if(ordi->QTable[s][i]>max){
//             max=ordi->QTable[s][i];
//             action=i;
//         }
//     }

//     return action;
// }

void initPartie(ordinateur_t *ordi1, ordinateur_t *ordi2, ball_t **ball, ball_t **precball)
{

    resetEmplacement(ordi1);
    resetEmplacement(ordi2);

    int rx = rand() % 3;
    rx--; // rx = -1, 0 ou 1
    int ry = rand() % 3;
    ry--;

    (*ball)->x += 200 * rx;
    (*ball)->y += 200 * ry;

    (*precball)->x += 200 * rx;
    (*precball)->y += 200 * ry;
}

void renforcement(ordinateur_t *ordi1, ordinateur_t *ordi2)
{ // Fonction principale

    int isGoal = 1, equipeBut = 0, nbActionPourReset = 0;
    int epoque, pas;
    float T = TEMPERATURE;
    int s1[NBEPOCH], a1[NBEPOCH - 1], r1[NBEPOCH]; // Liste états, actions et récompenses pour joueur 1
    int s2[NBEPOCH], a2[NBEPOCH - 1], r2[NBEPOCH]; // Liste états, actions et récompenses pour joueur 2

    player_t prec1, prec2;
    ball_t *ball;
    ball_t *precBall;

    ball = creationBall();
    precBall = creationBall();

    for (epoque = 0; epoque < MAXEPOCH; epoque++)
    {
        T = (TEMPERATURE - (epoque * 1.0 / MAXEPOCH) * TEMPERATURE) + 0.0001;
        // Reset le monde
        if (isGoal || nbActionPourReset >= 5)
        {
            isGoal = 0;
            nbActionPourReset = 0;
            initPartie(ordi1, ordi2, &ball, &precBall);
            copie(&prec1, ordi1->player);
            copie(&prec2, ordi2->player);
        }
        r1[0] = 0;
        r2[0] = 0;
        s1[0] = perception(*ball, *(ordi1->player), *(ordi2->player)); // Etat actuel joueur1
        s2[0] = perception(*ball, *(ordi2->player), *(ordi1->player)); // Etat actuel joueur2

        // Si c'est un apprentissage de qualité d'états : mettre à jour les successeurs de l'état perçu
        // a1[0] = choixAction(ordi1, s1[0], T);
        // a2[0] = choixAction(ordi2, s2[0], T);
        // printf("---------%d---------\n",epoque);

        for (pas = 1; pas < NBEPOCH; pas++)
        { // printf("\t-----%d-----\n",pas);
            // 1resetEmplacement itération du jeu
            a1[pas - 1] = choixAction(ordi1, s1[pas - 1], T);
            a2[pas - 1] = choixAction(ordi2, s2[pas - 1], T);
            if (rand() % 2)
            {
                faireAction(a1[pas - 1], ordi1, ball);
                faireAction(a2[pas - 1], ordi2, ball);
            }
            else
            {
                faireAction(a2[pas - 1], ordi2, ball);
                faireAction(a1[pas - 1], ordi1, ball);
            }

            isGoal = moveBall(ball, &equipeBut);
            r1[pas] = recompense(*precBall, *ball, prec1, *(ordi1->player), isGoal, equipeBut); // Récompense joueur1
            r2[pas] = recompense(*precBall, *ball, prec2, *(ordi2->player), isGoal, equipeBut); // Récompense joueur2
            s1[pas] = perception(*ball, *(ordi1->player), *(ordi2->player));                    // Etat actuel joueur1
            s2[pas] = perception(*ball, *(ordi2->player), *(ordi1->player));                    // Etat actuel joueur2

            copie(&prec1, ordi1->player);
            copie(&prec2, ordi2->player);
            copieBall(precBall,ball);
            // Si c'est un apprentissage de qualité d'états : mettre à jour les successeurs de l'état perçu

            // Appliquer l'action choisie au monde
            if (isGoal)
            { // Si l'état atteint est terminal : break => but
                // printf("\nBUUUUUUUUTTTTTTTT\n");
                pas++;
                break;
            }
        }
        pas--;
        nbActionPourReset++;
        evolution(ordi1, s1, a1, r1, pas);
        evolution(ordi2, s2, a2, r2, pas);
    }
    printf("fin renforcement");
    saveQTable("nario.don", ordi1->QTable);
    saveQTable("valuigi.don", ordi2->QTable);
    free(ball);
    free(precBall);
}

void resetEmplacement(ordinateur_t *ordi)
{
    int rx = rand() % 3;
    rx--; // rx = -1, 0 ou 1
    int ry = rand() % 3;
    ry--;
    if (EQUIPEGAUCHE == ordi->player->equipe)
    {
        ordi->player->x = WINDOWW / 4;
        ordi->player->y = WINDOWH / 2;
    }
    else
    {
        ordi->player->x = 3 * (WINDOWW / 4);
        ordi->player->y = WINDOWH / 2;
    }

    ordi->player->x = ordi->player->x + 200 * rx;
    ordi->player->y = ordi->player->y + 200 * ry;
}

void saveQTable(char *nom_fichier, float **QTable)
{
    FILE *file = fopen(nom_fichier, "w");
    if (file)
    {
        int i, j;
        for (i = 0; i < NBETATS; i++)
        {
            for (j = 0; j < NBACTIONS; j++)
            {
                fprintf(file, "%f ", QTable[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}

void chargerQTable(char *nom_fichier, float **Qtable)
{
    FILE *file = fopen(nom_fichier, "r");
    if (file)
    {
        int i, j;
        for (i = 0; i < NBETATS; i++)
        {
            for (j = 0; j < NBACTIONS; j++)
            {
                fscanf(file, "%f", &Qtable[i][j]);
            }
        }
        fclose(file);
    }
}

void faireAction(enum ACTIONS action, ordinateur_t *ordi, ball_t *ball)
{
    int angle = 0;
    switch (action)
    {
    case HAUT:

        movePlayer(ordi->player, HAUTD);
        break;
    case GAUCHE:

        movePlayer(ordi->player, GAUCHED);
        break;
    case BAS:

        movePlayer(ordi->player, BASD);
        break;
    case DROIT:

        movePlayer(ordi->player, DROITD);
        break;
    case HG:

        movePlayer(ordi->player, HGD);
        break;
    case HD:

        movePlayer(ordi->player, HDD);
        break;
    case BG:

        movePlayer(ordi->player, BGD);
        break;
    case BD:

        movePlayer(ordi->player, BDD);
        break;
    case TIR:

        if (ordi->player->equipe == EQUIPEGAUCHE)
        {
            int distance = sqrt(pow(ball->x - WINDOWW - WALLW, 2) + pow(ball->y - WINDOWH / 2, 2));
            int dx = +WINDOWW + WALLW - ball->x;
            float a = acos((float)dx / (float)distance * 1.0);
            angle = a * 180.0 / M_PI;
        }
        else
        {
            int distance = sqrt(pow(ball->x - WALLW, 2) + pow(ball->y - WINDOWH / 2, 2));
            int dx = WALLW - ball->x;
            float a = acos((dx * 1.0) / distance * 1.0);
            angle = a * 180.0 / M_PI;
        }
        pushBall(ball, angle, BALL_ACCELERATION);
        break;
    default:
        break;
    }
}

void copie(player_t *prec, player_t *ordi)
{
    prec->dir = ordi->dir;
    prec->equipe = ordi->equipe;
    prec->h = ordi->h;
    prec->w = ordi->w;
    prec->x = ordi->x;
    prec->y = ordi->y;
}

void copieBall(ball_t *prec, ball_t *ball)
{
    prec->size=ball->size;
    prec->theta=ball->size;
    prec->v=ball->v;
    prec->x=ball->x;
    prec->y=ball->y;
}
