#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>

#include "const.h"

#define BULLET_SCALE 0.5
#define BULLET_WIDTH 37
#define BULLET_HEIGHT 13
#define BULLET_SPEED 3

typedef struct bullet
{
    int x;
    int y;
    int w;
    int h;
} bullet_t;

int moveBullet(bullet_t *bullet);
void destroyBullet(bullet_t **bullet);
bullet_t *createBullet(int x, int y);

#endif