#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "player.h"
#include "playerAffichage.h"
#include "bullet.h"
#include "bulletAffichage.h"

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

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int arretEvent = 0, mouseX = 0, mouseY = 0;

    player_t *player;
    bullet_t *bullet = NULL;

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

    player = malloc(sizeof(player_t));
    if (player == NULL)
    {
        end_sdl(0, "ERROR MALLOC PLAYER", window, renderer);
    }
    player->x = 100;
    player->y = 100;
    if (loadPlayerTexture(renderer, player))
    {
        end_sdl(0, "ERROR Loading texture PLAYER", window, renderer);
    }

    SDL_Texture *bulletTexture = NULL;
    if (loadBulletTexture(renderer, &bulletTexture))
    {
        end_sdl(0, "ERROR Loading texture Bullet", window, renderer);
    }


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
                case SDLK_s:
                    movePlayerDown(player); // Fermeture du programme à l'appuie sur la touche ECHAP
                    arretEvent = 1;
                    break;
                case SDLK_z:
                    movePlayerUp(player); // Fermeture du programme à l'appuie sur la touche ECHAP
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
                  if (bullet != NULL)
                  {
                      destroyBullet(&bullet);
                  }
                  printf("Bulett go brrrr\n");
                  bullet = createBullet(player->x, player->y);
                  if (bullet == NULL)
                  {
                      end_sdl(0, "ERROR MALLOC PLAYER", window, renderer);
                  }
                }
                arretEvent = 1;
                break;
            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        arretEvent = 0;
        SDL_Delay(16);

        // Update cycle

        // Draw Frame
        SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle
        afficherVaisseau(renderer, player);
        if(bullet != NULL)
        {
            moveBullet(&bullet);
        }
        if (bullet != NULL)
        {
            printf("%d %d\n", bullet->x,bullet->y);
            afficherBullet(renderer, bullet, bulletTexture);
        }
        SDL_RenderPresent(renderer); // affichage
    }
    destroyPlayerTexture(player);
    destroyPlayer(player);
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}