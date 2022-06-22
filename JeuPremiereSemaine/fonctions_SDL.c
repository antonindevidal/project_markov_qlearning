#include "fonctions_SDL.h"

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{ // renderer à fermer
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

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *mon_image = NULL;  // Variable de passage
    SDL_Texture *ma_texture = NULL; // La texture

    mon_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                           // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                           // uniquement possible si l'image est au format bmp */
    if (mon_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    ma_texture = SDL_CreateTextureFromSurface(renderer, mon_image);
    SDL_FreeSurface(mon_image);
    if (ma_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return ma_texture;
}

void afficher_texture(SDL_Texture *ma_texture, SDL_Renderer *renderer, int w, int h, int x, int y)
{
    SDL_Rect source = {0}, destination = {0};

    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h);

    destination.w = w;
    destination.h = h;
    destination.x = x - w / 2;
    destination.y = y - h / 2;

    SDL_RenderCopy(renderer, ma_texture, &source, &destination);
}