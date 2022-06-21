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
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.5;                // Facteur de zoom à appliquer
    destination.w = source.w * zoom; // La destination est un zoom de la source
    destination.h = source.h * zoom; // La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) / 2;
    destination.y = (window_dimensions.h - destination.h) / 2;

    SDL_RenderCopy(renderer, ma_texture, &source, &destination);
}

void animation_image(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h);

    float zoom = 0.06; // Facteur de zoom entre l'image source et l'image affichée
    int nb_it = 200;   // Nombre d'images de l'animation
    destination.w = source.w * zoom;
    destination.h = source.h * zoom;
    destination.x = (window_dimensions.w - destination.w) / 2;
    float h = window_dimensions.h - destination.h; // le pas

    for (int i = 0; i < nb_it; ++i)
    {
        destination.y =
            h * (1 - exp(-5.0 * i / nb_it) / 2 *
                         (1 + cos(10.0 * i / nb_it * 2 * M_PI))); // hauteur en fonction du numéro d'image

        SDL_RenderClear(renderer);                                   // Effacer l'image précédente
        SDL_RenderCopy(renderer, ma_texture, &source, &destination); // Préparation de l'affichage
        SDL_RenderPresent(renderer);                                 // Affichage de la nouvelle image
        SDL_Delay(30);                                               // Pause en ms
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre une fois le travail terminé
}

void animation_sprite(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(ma_texture, NULL, NULL, &source.w, &source.h);

    int nb_images = 9; //Nombre d'images par ligne
    int nb_lignes = 3;
    float zoom = 2;   
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image
        offset_y = source.h / nb_lignes;         // La hauteur d'une vignette de l'image

    state.x = 0;            // La première vignette est en début de ligne
    state.y = 0 * offset_y; // On s'intéresse à la 1ère ligne
    state.w = offset_x;     // Largeur de la vignette
    state.h = offset_y;     // Hauteur de la vignette

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = (window_dimensions.h - destination.h) / 2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
    {
        destination.x = x;   // Position en x pour l'affichage du sprite
        state.x += offset_x; // On passe à la vignette suivante dans l'image
        state.x %= source.w; // La vignette qui suit celle de fin de ligne est
                             // celle de début de ligne

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, ma_texture, &state, &destination);
        SDL_RenderPresent(renderer); 
        SDL_Delay(80);           
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
}