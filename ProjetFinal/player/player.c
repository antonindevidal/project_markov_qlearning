#include "player.h"

player_t *createPlayer()
{
    player_t *p = malloc(sizeof(player_t));
    if (p != NULL)
    {
        p->x = WINDOWW / 4;
        p->y = WINDOWH / 2;
        p->dir = HAUTD;
        p->w = PLAYERWIDTH;
        p->h = PLAYERHEIGHT;
    }
    return p;
}

void movePlayer(player_t *p, enum DIRECTION dir)
{
    p->dir = dir;
    p->x += cos(p->dir * M_PI / 180) * PLAYER_SPEED ;
    p->y += sin(p->dir * M_PI / 180) * PLAYER_SPEED;
 
    if (p->x < WALLW)
        p->x = WALLW;
    if (p->x > WINDOWW - WALLW)
        p->x = WINDOWW - WALLW;
    if (p->y > WINDOWH)
        p->y = WINDOWH;
    if (p->y < 0)
        p->y = 0;
}

void playerBallCollision(player_t *p, ball_t *b)
{
}

void initQTableOrdi(ordinateur_t *ordi) {
    int i, j;
    for (i=0; i<NBETATS; i++) {
        for (j=0; j<NBACTIONS; j++) {
            ordi->QTable[i][j] = 0;
        }
    }
}