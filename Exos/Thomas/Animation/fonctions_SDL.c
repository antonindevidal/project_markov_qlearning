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

void afficher_texture_full(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    /* Affiche la texture sur la totalité de la fenêtre */
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, ma_texture, &source, &destination); // Création de l'élément à afficher
}

void afficher_texture(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.5;                // Facteur de zoom à appliquer
    destination.w = source.w * zoom; // La destination est un zoom de la source
    destination.h = source.h * zoom; // La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) / 2;
    destination.y = (window_dimensions.h - destination.h) / 2;

    SDL_RenderCopy(renderer, ma_texture, &source, &destination);
}