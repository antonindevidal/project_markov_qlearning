#include "fonctions_SDL.h"

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{
    // fin normale: ok=0, anormale: ok=1
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

void draw(SDL_Renderer *renderer, int pos, int couleur, int couleur_arc)
{
    SDL_Rect fond;
    fond.x = 0, fond.y = 0, fond.w = 500, fond.h = 500;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &fond);

    SDL_Rect rectangle;
    if (couleur)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Forme: RGBA
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Forme: RGBA
    }
    rectangle.x = 0, rectangle.y = 400;
    rectangle.w = 500, rectangle.h = 100;
    SDL_RenderFillRect(renderer, &rectangle);

    /* Dessin du personnage */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 200, 225, 300, 225); //(x,y) départ puis (x,y) fin -
    SDL_RenderDrawLine(renderer, 250, 150, 250, 300); // |
    SDL_RenderDrawLine(renderer, 250, 300, 200, 400); // /
    SDL_RenderDrawLine(renderer, 250, 300, 300, 400); // !/
    float angle = 0;
    for (angle = 0; angle < 2 * M_PI; angle += M_PI / 4000) // La tête
    {
        SDL_RenderDrawPoint(renderer, 250 + 50 * cos(angle), 100 + 50 * sin(angle));
    }
    if (pos)
    {
        SDL_RenderDrawLine(renderer, 200, 225, 200, 275);
        SDL_RenderDrawLine(renderer, 300, 225, 300, 175);
    }
    else
    {
        SDL_RenderDrawLine(renderer, 200, 225, 200, 175);
        SDL_RenderDrawLine(renderer, 300, 225, 300, 275);
    }
    
    /* Arc de cercle en haut à gauche pour essayer un animation qui bouge tout le temps */
    int i;
    for (i = 0; i < 100; i+=3)
    {
        for (angle = -M_PI / 2; angle < 0; angle += M_PI / 4000)
        {
            SDL_SetRenderDrawColor(renderer, couleur_arc, 255 - couleur_arc, 0, 255);
            SDL_RenderDrawPoint(renderer, i * cos(angle), - i * sin(angle));
        }
    }
}