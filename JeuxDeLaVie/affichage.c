#include "affichage.h"

void afficherGrille(int **nouv, int tailleX, int tailleY, int tailleCell, SDL_Renderer *renderer)
{
    for (int i = 0; i < tailleX; i++)
    {
        for (int j = 0; j < tailleY; j++)
        {
            afficherCase(renderer, nouv[i][j], i * tailleCell, j * tailleCell, tailleCell);
        }
    }
}

void afficherCase(SDL_Renderer *renderer, int value, int posX, int posY, int tailleCell)
{

    if (value == 0)
    {
        SDL_Rect rect;
        rect.x = posX;
        rect.y = posY;
        rect.h = tailleCell;
        rect.w = tailleCell;
        SDL_SetRenderDrawColor(renderer,
                               255, 255, 255,
                               255);    

        SDL_RenderFillRect(renderer, &rect);
    }
}