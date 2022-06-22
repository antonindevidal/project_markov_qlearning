#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include "ennemis.h"

#define WINDOWH 400
#define WINDOWW 500

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
    destination.x = x - w/2;
    destination.y = y - h/2;

    SDL_RenderCopy(renderer, ma_texture, &source, &destination);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int arretEvent=0,mouseX=0,mouseY=0,cycles=0;
    int nbCycles=1;

    /* Ennemis */
    int x_ufoBlue=250, y_ufoBlue=200, w_ufoBlue=50, h_ufoBlue=50;
    int theta=0;
    int vitesseX=10, vitesseY=5;


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
                {                                                                           // Si c'est un click gauche
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
        afficher_texture(ufoBlue, renderer, w_ufoBlue, h_ufoBlue, x_ufoBlue, y_ufoBlue);

        // Update cycle
        if (cycles >= nbCycles) 
        {
            cycles = 0;
            deplacement(&x_ufoBlue, &y_ufoBlue, theta, vitesseX, vitesseY);
            theta += 10;
        }

        // Draw Frame

        SDL_RenderPresent(renderer); // affichage
    }
    
    SDL_DestroyTexture(ufoBlue);
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}