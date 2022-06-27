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

void pushBall(ball_t *b, int angle)
{
    b->theta = angle;
    b->v += BALL_ACCELERATION;
}

void moveBall(ball_t *b)
{
    b->x += cos(b->theta * M_PI / 180) * b->v;
    b->y += sin(b->theta * M_PI / 180) * b->v;

    collisionBall(b);

    b->v -= FROTEMENTS;
    if (b->v < 0)
        b->v = 0;
}

void collisionBall(ball_t *b)
{
    if (b->x > WINDOWW - WALLW)
    {
        b->theta = 180 - b->theta;
        b->x = WINDOWW - WALLW;
    }
    else if (b->x < WALLW)
    {
        b->theta = 180 - b->theta;
        b->x = WALLW;
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
}