#ifndef BULLET_LIST
#define BULLET_LIST


typedef struct bulletList
{
    bullet_t *bullet;
    struct bulletList *suiv;
}maillonB_t,*listB_t;

#endif