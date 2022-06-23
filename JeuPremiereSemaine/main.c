#include <string.h>
#include <time.h>

#include "ennemis.h"
#include "const.h"
#include "player.h"
#include "playerAffichage.h"
#include "bullet.h"
#include "bulletAffichage.h"
#include "score.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    (void)argc;
    (void)argv;
    int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = 0;
    int nbCycles = 1;
    int score = 0;

    /* Player */
    player_t *player;
    bullet_t *bullet = NULL;

    /* Ennemis */
    listEnnemis_t ennemis;
    initEnnemi(&ennemis);
    ajoutEnnemi(&ennemis, 350, 50, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 300, 250, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 350, 300, 20, 20, 20, 40);
    ajoutEnnemi(&ennemis, 320, 150, 20, 20, 20, 40);

    SDL_bool programON = SDL_FALSE;
    SDL_bool finON = SDL_TRUE;
    SDL_Event event;

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

    while (finON)
    { // Boucle événementielle de l'écran de fin
        SDL_FlushEvent(SDL_MOUSEMOTION);
        while (SDL_PollEvent(&event) && !arretEvent)
        {
            switch (event.type)
            {                          // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:             // Un évènement simple, on a cliqué sur la x de la fenêtre
                finON = SDL_FALSE; // Il est temps d'arrêter le programme
                arretEvent = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    finON = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
                    arretEvent = 1;
                    break;
                case SDLK_SPACE: // On recommence le jeu avec la barre espace
                    score = 0;
                    finON = SDL_FALSE;
                    programON = SDL_TRUE;
                default:
                    break;
                }
                break;
            default: 
                break;
            }
        }
        arretEvent = 0;
        cycles++;
        SDL_Delay(50);

        // Update cycle

        // Draw Frame
        SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle
        finScore(score, font, window, renderer);
        SDL_RenderPresent(renderer); // affichage
    }

    while (programON)
    { // Boucle événementielle du jeu
        SDL_FlushEvent(SDL_MOUSEMOTION);
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
                    bullet = createBullet(player->x, player->y);
                    if (bullet == NULL)
                    {
                        endSDL(0, "ERROR MALLOC PLAYER", window, renderer);
                    }
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
        if (bullet != NULL)
        {
            moveBullet(&bullet);
        }
        if (bullet != NULL)
        {
            afficherBullet(renderer, bullet, bulletTexture);
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