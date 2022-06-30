#include "player.h"

player_t *createPlayer(enum EQUIPE equipe)
{
    player_t *p = malloc(sizeof(player_t));
    if (p != NULL)
    {
        if (EQUIPEGAUCHE == equipe)
        {
            p->x = WINDOWW / 4;
            p->y = WINDOWH / 2;
            p->dir = HAUTD;
        }
        else
        {
            p->x = 3 * (WINDOWW / 4);
            p->y = WINDOWH / 2;
            p->dir = BASD;
        }

        
        p->w = PLAYERWIDTH;
        p->h = PLAYERHEIGHT;
        p->equipe = equipe;
    }
    return p;
}

void movePlayer(player_t *p, enum DIRECTION dir)
{
    p->dir = dir;
    p->x += cos(p->dir * M_PI / 180) * PLAYER_SPEED;
    p->y += sin(p->dir * M_PI / 180) * PLAYER_SPEED;

    if (p->x < WALLW + PLAYERWIDTH / 2)
        p->x = WALLW + PLAYERWIDTH / 2;
    if (p->x > WINDOWW - WALLW - PLAYERWIDTH / 2)
        p->x = WINDOWW - WALLW - PLAYERWIDTH / 2;
    if (p->y > WINDOWH - PLAYERHEIGHT / 2)
        p->y = WINDOWH - PLAYERHEIGHT / 2;
    if (p->y < PLAYERHEIGHT / 2)
        p->y = PLAYERHEIGHT / 2;
}

void playerBallCollision(player_t *p, ball_t *b)
{
    int distance = sqrt(pow(p->x - b->x, 2) + pow(p->y - b->y, 2));
    int diam = b->size / 2 + p->w / 2;

    if (distance < diam)
    {
        int t = b->x - p->x;
        float a = acos((t * 1.0) / distance * 1.0);
        float angle = a * 180.0 / M_PI;
        if (b->y < p->y)
        {
            angle = -1 * angle;
        }
        pushBall(b, angle, 5);
    }
}
