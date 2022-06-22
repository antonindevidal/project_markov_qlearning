#include "playerAffichage.h"

/// Load player texture
///  return 1 if error
///  return 0 if not
int loadPlayerTexture(SDL_Renderer *renderer, player_t *player)
{
    player->texture = IMG_LoadTexture(renderer, SPRITE_PLAYER);
    if (player->texture != NULL)
    {
        SDL_QueryTexture(player->texture, NULL, NULL,
                         &(player->w), &(player->h)); // Récupération des dimensions de l'image
    }
    return player->texture == NULL;
}
void destroyPlayerTexture(player_t *player)
{
    SDL_DestroyTexture(player->texture);
}

void afficherVaisseau(SDL_Renderer *renderer, player_t *player)
{
    SDL_Rect
        source = {0},      // Rectangle définissant la zone de la texture à récupérer
        destination = {0}; // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_QueryTexture(player->texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination.w = source.w * SCALE; // La destination est un zoom de la source
    destination.h = source.h * SCALE; // La destination est un zoom de la source
    destination.x = player->x - source.w / 2;
    destination.y = player->y - source.h / 2;

    SDL_RenderClear(renderer);                // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_RenderCopy(renderer, player->texture, // Préparation de l'affichage
                   &source,
                   &destination);
}
