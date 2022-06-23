#include "fonctionsSDL.h"

void endSDL(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // renderer à fermer
    char msgFormated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msgFormated, msg, 250);
        l = strlen(msgFormated);
        strcpy(msgFormated + l, " : %s\n");

        SDL_Log(msgFormated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *loadTextureFromImage(char *fileImageName, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *monImage = NULL;  // Variable de passage
    SDL_Texture *maTexture = NULL; // La texture

    monImage = IMG_Load(fileImageName); // Chargement de l'image dans la surface
                                        // image=SDL_LoadBMP(fileImageName); fonction standard de la SDL,
                                        // uniquement possible si l'image est au format bmp */
    if (monImage == NULL)
        endSDL(0, "Chargement de l'image impossible", window, renderer);

    maTexture = SDL_CreateTextureFromSurface(renderer, monImage);
    SDL_FreeSurface(monImage);
    if (maTexture == NULL)
        endSDL(0, "Echec de la transformation de la surface en texture", window, renderer);

    return maTexture;
}

void afficherTexture(SDL_Texture *maTexture, SDL_Renderer *renderer, int w, int h, int x, int y)
{
    SDL_Rect source = {0}, destination = {0};

    SDL_QueryTexture(maTexture, NULL, NULL, &source.w, &source.h);

    destination.w = w;
    destination.h = h;
    destination.x = x - w / 2;
    destination.y = y - h / 2;

    SDL_RenderCopy(renderer, maTexture, &source, &destination);
}