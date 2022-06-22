#include <string.h>
#include "ennemis.h"

#define WINDOWH 400
#define WINDOWW 500

int main(int argc, char **argv)
{
    srand(time(NULL));
    (void)argc;
    (void)argv;
    int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = 0;
    int nbCycles = 1;

    /* Ennemis */
    ennemis_t ennemis;
    init_ennemi(&ennemis);
    ajout_ennemi(&ennemis, 50, 50, 20, 20, 10, 20);

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOWW,
                              WINDOWH,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /* Création des textures */
    SDL_Texture *ufoBlue = load_texture_from_image("resources/ennemis/ufoBlue.png", window, renderer);
    SDL_Texture *ufoGreen = load_texture_from_image("resources/ennemis/ufoGreen.png", window, renderer);
    SDL_Texture *ufoRed = load_texture_from_image("resources/ennemis/ufoRed.png", window, renderer);
    SDL_Texture *ufoYellow = load_texture_from_image("resources/ennemis/ufoYellow.png", window, renderer);
    SDL_Texture *meteorBrown_big1 = load_texture_from_image("resources/ennemis/meteorBrown_big1.png", window, renderer);
    SDL_Texture *meteorBrown_small1 = load_texture_from_image("resources/ennemis/meteorBrown_small1.png", window, renderer);

    while (program_on)
    {
        SDL_FlushEvent(SDL_MOUSEMOTION);
        while (SDL_PollEvent(&event) && !arretEvent)
        {
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                arretEvent = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    program_on = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
                    arretEvent = 1;
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_GetMouseState(&mouseX, &mouseY) &
                    SDL_BUTTON(SDL_BUTTON_LEFT))
                { // Si c'est un click gauche
                }
                arretEvent = 1;
                break;
            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        arretEvent = 0;
        cycles++;
        SDL_Delay(16);
        afficher_ennemis(&ennemis, ufoBlue, renderer);

        // Update cycle
        if (cycles >= nbCycles)
        {
            cycles = 0;
            
        }

        // Draw Frame

        SDL_RenderPresent(renderer); // affichage
    }

    SDL_DestroyTexture(ufoBlue);
    SDL_DestroyTexture(ufoGreen);
    SDL_DestroyTexture(ufoRed);
    SDL_DestroyTexture(ufoYellow);
    SDL_DestroyTexture(meteorBrown_big1);
    SDL_DestroyTexture(meteorBrown_small1);
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}