#include "ball.h"

ball_t *creationBall()
{
    ball_t *b = malloc(sizeof(ball_t));
    if (b != NULL)
    {
        b->x = WINDOWW / 2;
        b->y = WINDOWH / 2;
        b->v = 0;
        b->theta = 0;
        b->size = BALLSIZE;
    }
    return b;
}

void pushBall(ball_t *b, int angle, int power)
{
    b->theta = angle;
    b->v += power;
    if (b->v > MAX_VELOCITY)
        b->v = MAX_VELOCITY;
}

int moveBall(ball_t *b, enum EQUIPE *e)
{
    b->x += cos(b->theta * M_PI / 180) * b->v;
    b->y += sin(b->theta * M_PI / 180) * b->v;

    int but = collisionBall(b, e);

    b->v -= FROTEMENTS;
    if (b->v < 0)
        b->v = 0;
    return but;
}

int collisionBall(ball_t *b, enum EQUIPE *e)
{
    int but = 0;
    if (b->x > WINDOWW - WALLW)
    {
        b->theta = 180 - b->theta;
        b->x = WINDOWW - WALLW;
        if (b->y > WINDOWH / 2 - GOALSIZE / 2 && b->y < WINDOWH - GOALSIZE / 2)
        {
            but = 1;
            *e = EQUIPEGAUCHE;
        }
    }
    else if (b->x < WALLW)
    {
        b->theta = 180 - b->theta;
        b->x = WALLW;
        if (b->y > WINDOWH / 2 - GOALSIZE / 2 && b->y < WINDOWH - GOALSIZE / 2)
        {
            but = 1;
            *e = EQUIPEDROITE;
        }
    }
    else if (b->y < 0)
    {
        b->theta = -b->theta;
        b->y = 0;
    }
    else if (b->y > WINDOWH)
    {
        b->theta = -b->theta;
        b->y = WINDOWH;
    }
    return but;
}