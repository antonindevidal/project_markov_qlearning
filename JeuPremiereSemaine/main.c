#include <string.h>
#include <time.h>

#include "ennemis.h"
#include "const.h"
#include "player.h"
#include "playerAffichage.h"
#include "bullet.h"
#include "bulletAffichage.h"
#include "score.h"

#include "bulletList.h"

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
    srand(time(NULL));
    (void)argc;
    (void)argv;
    int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = 0;
    int nbCycles = 1;
    int score=0;

    /* Player */
    player_t *player;

    /* Ennemis */
    listEnnemis_t ennemis;
    initEnnemi(&ennemis);
    ajoutEnnemi(&ennemis, 350, 50, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 300, 250, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 350, 300, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 320, 150, 20, 20, 20, 40);

    SDL_bool programON = SDL_TRUE; 
    SDL_Event event;              
    listB_t listeBullet;
    listeBullet=initListeBullet();
    

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        endSDL(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOWW,
                              WINDOWH,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        endSDL(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    SDL_Texture *ufoBlue = loadTextureFromImage("resources/ennemis/ufoBlue.png", window, renderer);
    SDL_Texture *ufoGreen = loadTextureFromImage("resources/ennemis/ufoGreen.png", window, renderer);
    SDL_Texture *ufoRed = loadTextureFromImage("resources/ennemis/ufoRed.png", window, renderer);
    SDL_Texture *ufoYellow = loadTextureFromImage("resources/ennemis/ufoYellow.png", window, renderer);
    SDL_Texture *meteorBrownBig1 = loadTextureFromImage("resources/ennemis/meteorBrownBig1.png", window, renderer);
    SDL_Texture *meteorBrownSmall1 = loadTextureFromImage("resources/ennemis/meteorBrownSmall1.png", window, renderer);
    SDL_Texture *bulletTexture = NULL;
    
    player = malloc(sizeof(player_t));
    if (player == NULL)
    {
        endSDL(0, "ERROR MALLOC PLAYER", window, renderer);
    }
    player->x = 100;
    player->y = 100;
    if (loadPlayerTexture(renderer, player))
    {
        endSDL(0, "ERROR Loading texture PLAYER", window, renderer);
    }

    if (loadBulletTexture(renderer, &bulletTexture))
    {
        endSDL(0, "ERROR Loading texture Bullet", window, renderer);
    }

    while (programON)
    {
        SDL_FlushEvent(SDL_MOUSEMOTION);
        while (SDL_PollEvent(&event) && !arretEvent)
        {
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
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
                  ajoutEnTeteBullet(player->x,player->y,&listeBullet);
                }
                arretEvent = 1;
                break;
            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        arretEvent = 0;
        cycles++;
        SDL_Delay(50);
        
        // Update cycle
        if (cycles >= nbCycles)
        {
            cycles = 0;
            deplacementEnnemis(&ennemis);
            
        }

        // Draw Frame
        SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle
        afficherVaisseau(renderer, player);
        afficherEnnemis(ennemis, ufoBlue, renderer);
        afficherScore(score, font, window, renderer);
        //printf("%d \n",IsVideB(listeBullet));
        if(!IsVideB(listeBullet))
        {
            moveAllBullet(&listeBullet);
            afficherAllBullet(renderer, listeBullet, bulletTexture);
        }

        SDL_RenderPresent(renderer); // affichage
    }

    destroyPlayerTexture(player);
    destroyPlayer(player);

    liberationEnnemis(ennemis);
    SDL_DestroyTexture(ufoBlue);
    SDL_DestroyTexture(ufoGreen);
    SDL_DestroyTexture(ufoRed);
    SDL_DestroyTexture(ufoYellow);
    SDL_DestroyTexture(meteorBrownBig1);
    SDL_DestroyTexture(meteorBrownSmall1);
    endSDL(1, "Normal ending", window, renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}