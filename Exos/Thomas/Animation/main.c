#include "fonctions_SDL.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode ecran;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        end_sdl(0, "Erreur: SDL INIT", window, renderer);
    }

    SDL_GetCurrentDisplayMode(0, &ecran);
    printf("Résolution écran: %d x %d\n", ecran.w, ecran.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Animation", ecran.w / 2 - 250, ecran.h / 2 - 250, 500, 500, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        end_sdl(0, "Erreur: WINDOW CREATION", window, renderer);
    }

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "Erreur: RENDERER CREATION", window, renderer);
    }

    /* Création des textures */
    SDL_Texture *image_fond = load_texture_from_image("images/image_fond.jpg", window, renderer);
    SDL_Texture *michelin = load_texture_from_image("images/michelin.png", window, renderer);
    SDL_Texture *bateau = load_texture_from_image("images/bateau.jpg", window, renderer);
    SDL_Texture *sprite = load_texture_from_image("images/Player/player_tilesheet.png", window, renderer);
    animation_sprite(sprite, window, renderer);
    animation_image(bateau, window, renderer);
    
    /* Gestion des événements */
    SDL_bool en_cours = SDL_TRUE;
    SDL_Event event;
    while (en_cours)
    { // Boucle événementielle
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: // On s'arrête quand l'utilisateur appuie sur la croix
                en_cours = SDL_FALSE;
                break;
            default:
                break;
            }
        }
        afficher_texture_full(image_fond, window, renderer);
        afficher_texture(michelin, window, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(30); // Faire une pause pour une bonne fluidité
    }
    

    SDL_DestroyTexture(image_fond);
    SDL_DestroyTexture(michelin);
    SDL_DestroyTexture(bateau);
    end_sdl(1, "Fin Normale", window, renderer);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}