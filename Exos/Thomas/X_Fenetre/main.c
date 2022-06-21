#include <stdio.h>
#include <SDL2/SDL.h>
#define TAILLE_LISTE_FENETRES 5

void createWindow(SDL_Window **pWindow, char *titre, int x, int y, int w, int h, Uint32 flags)
{
    *pWindow = SDL_CreateWindow(titre, x, y, w, h, flags);
    if (*pWindow == NULL)
    {
        SDL_Log("Erreur: SDL Window création - %s\n", SDL_GetError());
        SDL_DestroyWindow(*pWindow);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* A bien faire avant SDL_Init ! Sinon problème de descripteur */
    SDL_Window **fenetres;
    fenetres = (SDL_Window **)malloc(TAILLE_LISTE_FENETRES * sizeof(SDL_Window *));

    /* Initialisation de la SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur: Initialisation SDL - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_DisplayMode dim;
    SDL_GetCurrentDisplayMode(0, &dim);
    printf("Dimension écran: %i x %i\n", dim.w, dim.h);
    int largeur_fenetres = 200;
    int hauteur_fenetres = 100;
    int pos_X = dim.w / 2 - largeur_fenetres / 2;
    int pos_Y = dim.h / 2 - hauteur_fenetres / 2;
    createWindow(&fenetres[0], "Fenêtre 0", pos_X, pos_Y, largeur_fenetres, hauteur_fenetres, SDL_WINDOW_RESIZABLE);
    SDL_Delay(1000);
    int x = pos_X, y = pos_Y;
    while ((x + largeur_fenetres < dim.w - 200) && (y > 200))
    {
        x++;
        y--;
        SDL_SetWindowPosition(fenetres[0], x, y);
        SDL_Delay(5);
    }

    SDL_Delay(1000);
    createWindow(&fenetres[1], "Fenêtre 1", pos_X, pos_Y, largeur_fenetres, hauteur_fenetres, SDL_WINDOW_RESIZABLE);
    x = pos_X, y = pos_Y;
    while ((x > 200) && (y > 200))
    {
        x--;
        y--;
        SDL_SetWindowPosition(fenetres[1], x, y);
        SDL_Delay(5);
    }

    createWindow(&fenetres[2], "Fenêtre 2", pos_X, pos_Y, largeur_fenetres, hauteur_fenetres, SDL_WINDOW_RESIZABLE);
    x = pos_X, y = pos_Y;
    while ((x > 200) && (dim.h - 200 > y + hauteur_fenetres))
    {
        x--;
        y++;
        SDL_SetWindowPosition(fenetres[2], x, y);
        SDL_Delay(5);
    }

    createWindow(&fenetres[3], "Fenêtre 3", pos_X, pos_Y, largeur_fenetres, hauteur_fenetres, SDL_WINDOW_RESIZABLE);
    x = pos_X, y = pos_Y;
    while ((x + largeur_fenetres < dim.w - 200) && (dim.h - 200 > y + hauteur_fenetres))
    {
        x++;
        y++;
        SDL_SetWindowPosition(fenetres[3], x, y);
        SDL_Delay(5);
    }
    createWindow(&fenetres[4], "Fenêtre 4", pos_X, pos_Y, largeur_fenetres, hauteur_fenetres, SDL_WINDOW_RESIZABLE);
    SDL_Delay(1000); // En ms

    /* Fermeture des fenêtres */
    int i;
    for (i = 0; i < TAILLE_LISTE_FENETRES; i++)
    {
        if (fenetres[i] != NULL)
        {
            SDL_DestroyWindow(fenetres[i]);
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        free(fenetres[i]);
    }
    free(fenetres);

    SDL_Quit();
}