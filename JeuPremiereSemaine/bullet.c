#include "bullet.h"

void moveBullet(bullet_t **bullet)
{
    (*bullet)->x += BULLET_SPEED;
    if ((*bullet)->x > WINDOWW)
    {
        destroyBullet(bullet);
    }
}
void destroyBullet(bullet_t **bullet)
{
    if (*bullet != NULL)
    {
        free(*bullet);
        *bullet = NULL;
    }
}
bullet_t *createBullet(int x, int y)
{
    bullet_t *bullet = malloc(sizeof(bullet));
    if (bullet != NULL)
    {
        bullet->h = BULLET_HEIGHT; // Constant for the moment but may change if we implement bonuses
        bullet->w = BULLET_WIDTH;
        bullet->x = x;
        bullet->y = y;
    }
    return bullet;
}
