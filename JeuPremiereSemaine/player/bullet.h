#ifndef BULLET_H
#define BULLET_H

#define BULLET_SCALE 0.5
#define BULLET_WIDTH 37
#define BULLET_HEIGHT 13


typedef struct bullet
{
    int x;
    int y;
    int w = BULLET_WIDTH;
    int h = BULLET_HEIGHT;
};


#endif