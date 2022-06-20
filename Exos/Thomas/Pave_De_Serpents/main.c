#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "fonctions_SDL.h"

int main(int argc, char **argv)
{
    /* 
     * Si on appuie sur A alors on modifie le sens des bras du personnage
     * Si on clique avec la souris, on modifie la couleur du rectangle 
     * Si on appuie sur la barre espace, l'image se met en pause:
     * (pas de changement de couleur sur l'arc de cercle en haut à gauche)
     */
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
    window = SDL_CreateWindow("Premier dessin", ecran.w/2 - 250, ecran.h/2 - 250, 500, 500, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        end_sdl(0, "Erreur: WINDOW CREATION", window, renderer);
    }

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "Erreur: RENDERER CREATION", window, renderer);
    }

    int pos = 1, couleur_fond = 1, couleur_arc = 0;
    SDL_bool en_cours = SDL_TRUE, pause = SDL_FALSE;
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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                case SDLK_a:
                    pos = !pos; // On passe d'une position du perso à l'autre
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                couleur_fond = !couleur_fond;
                break;
            default:
                break;
            }
        }
        if (!pause) {
            draw(renderer, pos, couleur_fond, couleur_arc);
        }
        if (couleur_arc == 255) 
        {
            couleur_arc = -1;
        }
        couleur_arc+=10;
        SDL_RenderPresent(renderer);
        SDL_Delay(30); // Faire une pause pour une bonne fluidité
    }

    end_sdl(1, "Fin Normale", window, renderer);
    return EXIT_SUCCESS;
}