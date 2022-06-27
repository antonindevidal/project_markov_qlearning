#include <string.h>
#include <time.h>

#include "score.h"
#include "menus.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = -1;
    int score = 0;
    int etat = 0;

    SDL_bool programON = SDL_TRUE;
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        endSDL(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("TITRE DU JEU",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOWW,
                              WINDOWH,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        endSDL(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        endSDL(0, "ERROR RENDERER CREATION", window, renderer);

    /* Initialisation Font */
    if (TTF_Init() < 0)
        endSDL(0, "Erreur initialisation SDL TTF", window, renderer);

    TTF_Font *font = NULL;
    font = TTF_OpenFont("./resources/font/kenvector_future.ttf", 45);
    if (font == NULL)
        endSDL(0, "Erreur chargement Font", window, renderer);

    /* Création des textures */
    // A REMPLIR

    /* Boucle du jeu */
    while (programON)
    {                              // Boucle événementielle du programme
        SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle

        SDL_FlushEvent(SDL_MOUSEMOTION);
        switch (etat)
        {
        case 0: // Etat: Jeu
            while (SDL_PollEvent(&event) && !arretEvent)
            {
                switch (event.type)
                {                          // En fonction de la valeur du type de cet évènement
                case SDL_QUIT:             // Un évènement simple, on a cliqué sur la x de la fenêtre
                    programON = SDL_FALSE; // Il est temps d'arrêter le programme
                    arretEvent = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        programON = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
                        arretEvent = 1;
                        break;
                    default:
                        break;
                    }
                    break;
                default: // L'évènement défilé ne nous intéresse pas
                    break;
                }
            }
            arretEvent = 0;
            cycles++;

            /* Update cycle */
            // A REMPLIR

            /* Draw frame */
            afficherScore(score, font, window, renderer);

            break;
        case 1: // Etat: Fin
            while (SDL_PollEvent(&event) && !arretEvent)
            {
                switch (event.type)
                {              // En fonction de la valeur du type de cet évènement
                case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la fenêtre
                    programON = SDL_FALSE;
                    arretEvent = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        programON = SDL_FALSE;
                        arretEvent = 1;
                        break;
                    case SDLK_SPACE: // On recommence le jeu avec la barre espace
                        // score = 0;
                        arretEvent = 1;
                        etat = 0;
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            arretEvent = 0;
            // Draw Frame
            break;
        default:
            break;
        }
        SDL_Delay(20);
        SDL_RenderPresent(renderer); // affichage
    }

    TTF_CloseFont(font);
    endSDL(1, "Normal ending", window, renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}