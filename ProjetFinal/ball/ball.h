#ifndef BALL_H
#define BALL_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../const.h"

#define FROTEMENTS 0.01
#define BALL_ACCELERATION 20
#define BALLSIZE 40

typedef struct ball{
    int x;
    int y;
    int theta;
    int v;
    int size;
}ball_t;


ball_t *creationBall();
void pushBall(ball_t *b, int angle);
void moveBall(ball_t *b);
void collisionBall(ball_t *b);

#endif