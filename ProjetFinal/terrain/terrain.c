#include "terrain.h"

void afficherTerrain(SDL_Texture *texture, SDL_Renderer *renderer)
{

    for (int i = 0; i < (WINDOWW / TERRAINSPRITESIZE) + 1; i++)
    {
        for (int j = 0; j < (WINDOWH / TERRAINSPRITESIZE) + 1; j++)
        {
            afficherTileTerrain(j, i, texture, renderer);
        }
    }

    SDL_Rect haut = {0}, bas = {0}, gauche = {0}, droite = {0},goal = {0};
    haut.x = WALLW;
    haut.y = WALLH;
    haut.w = WINDOWW - 2 * WALLW;
    haut.h = LINETHICKNESS;

    bas.x = WALLW;
    bas.y = WINDOWH - WALLH - LINETHICKNESS;
    bas.w = WINDOWW - 2 * WALLW;
    bas.h = LINETHICKNESS;

    gauche.x = WALLW;
    gauche.y = WALLH;
    gauche.w = LINETHICKNESS;
    gauche.h = WINDOWH - 2 * WALLH;

    droite.x = WINDOWW - WALLW- LINETHICKNESS;
    droite.y = WALLH;
    droite.w = LINETHICKNESS;
    droite.h = WINDOWH - 2 * WALLH;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &haut);
    SDL_RenderFillRect(renderer, &bas);
    SDL_RenderFillRect(renderer, &gauche);
    SDL_RenderFillRect(renderer, &droite);

    goal.x = 0;
    goal.y = (WINDOWH - GOALSIZE)/2;
    goal.h = GOALSIZE;
    goal.w = WALLW;
    SDL_RenderFillRect(renderer, &goal);
    goal.x = WINDOWW - WALLW;
    goal.y = (WINDOWH - GOALSIZE)/2;
    goal.h = GOALSIZE;
    goal.w = WALLW;
    SDL_RenderFillRect(renderer, &goal);
}

void afficherTileTerrain(int i, int j, SDL_Texture *texture, SDL_Renderer *renderer)
{
    SDL_Rect source = {0}, destination = {0};
    source.x = 0;
    source.y = 0;

    source.w = TERRAINSPRITESIZE;
    source.h = TERRAINSPRITESIZE;

    destination.w = source.w;
    destination.h = source.h;
    destination.x = j * 32;
    destination.y = i * 32;

    SDL_RenderCopy(renderer, texture, &source, &destination);
}