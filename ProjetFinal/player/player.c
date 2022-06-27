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
    int distance = sqrt(pow(p->x - b->x, 2) + pow(p->y - b->y, 2));
    int diam = b->size;

    if (distance < diam)
    {
        float angle =0;
        int t = b->x - p->x;
        if (t!=0) angle = acos(distance/t)* 180 / M_PI;
        printf("h: %d a: %d\n",distance,t);
        pushBall(b,angle);
    }

}