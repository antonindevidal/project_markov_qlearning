#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#define WINDOWH 400
#define WINDOWW 500
#define CELLSIZE 10

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
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

// Create grid: return 0 if no errors
int creationGrille(int **nouv, int **anc)
{
    int error = 0;
    nouv = malloc(sizeof(int *) * (WINDOWW / CELLSIZE));
    if (nouv != NULL)
    {
        for(int i = 0;i <WINDOWW / CELLSIZE;i++)
        {
            nouv[i] = malloc(sizeof(int *) * (WINDOWW / CELLSIZE));
            if (nouv == NULL)
            {
                error = 1;
            }
        }
    }
    else
    {
        error = 1;
    }
    anc = malloc(sizeof(int *) * (WINDOWW / CELLSIZE));
    if (anc != NULL)
    {
        for(int i = 0;i <WINDOWW / CELLSIZE;i++)
        {
            nouv[i] = malloc(sizeof(int *) * (WINDOWW / CELLSIZE));
            if (anc == NULL)
            {
                error = 1;
            }
        }
    }
    else
    {
        error = 1;
    }
    return error;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int **nouv = NULL, **anc = NULL;

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

    if (creationGrille(nouv, anc))
    {
        end_sdl(0, "ERROR GRID CREATION MALLOC", window, renderer);
    }
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

    while (program_on)
    {
        SDL_FlushEvent(SDL_MOUSEMOTION);
        SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    program_on = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
                    break;

                default:
                    break;
                }

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }

        // Update cycle

        // Draw Frame

        SDL_RenderPresent(renderer); // affichage
        SDL_Delay(100);
    }

    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}