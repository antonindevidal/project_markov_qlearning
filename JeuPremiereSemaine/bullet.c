#include "bullet.h"

int moveBullet(bullet_t *bullet)
{
    bullet->x += BULLET_SPEED;
    if (bullet->x > WINDOWW)
    {
        return 1;
    }
    return 0;
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
    bullet_t *bullet = (bullet_t *)malloc(sizeof(bullet_t));
    if (bullet != NULL)
    {
        bullet->h = BULLET_HEIGHT; // Constant for the moment but may change if we implement bonuses
        bullet->w = BULLET_WIDTH;
        bullet->x = x;
        bullet->y = y;
    }
    return bullet;
}
