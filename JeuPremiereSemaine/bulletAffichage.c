#include "bulletAffichage.h"

/// Load BUllet texture
///  return 1 if error
///  return 0 if not
int loadBulletTexture(SDL_Renderer *renderer, SDL_Texture **texture)
{
    *texture = IMG_LoadTexture(renderer, SPRITE_BULLET);

    return texture == NULL;
}

void afficherBullet(SDL_Renderer *renderer, bullet_t *bullet,SDL_Texture *texture)
{
    SDL_Rect
        source = {0},      // Rectangle définissant la zone de la texture à récupérer
        destination = {0}; // Rectangle définissant où la zone_source doit être déposée dans le renderer

    source.h = bullet->h;
    source.w = bullet->w;
    source.x = 0;
    source.y = 0;
    destination.w = bullet->w ; // La destination est un zoom de la source
    destination.h = bullet->h ; // La destination est un zoom de la source
    destination.x = bullet->x - bullet->w / 2;
    destination.y = bullet->y - bullet->h / 2;

    SDL_RenderCopy(renderer, texture, // Préparation de l'affichage
                   &source,
                   &destination);
}

