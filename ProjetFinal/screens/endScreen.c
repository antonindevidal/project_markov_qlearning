#include "endScreen.h"

void ecranFin(SDL_Window *window, TTF_Font *font, SDL_Renderer *renderer, SDL_Event event, int *score1, int *score2, player_t *p, ball_t *b, int *debutTimer, int *etat, SDL_bool *programON, Mix_Music *musiqueJeu)
{
    int arretEvent = 0;
    while (SDL_PollEvent(&event) && !arretEvent)
    {
        switch (event.type)
        {              // En fonction de la valeur du type de cet évènement
        case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la fenêtre
            *programON = SDL_FALSE;
            arretEvent = 1;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *programON = SDL_FALSE;
                arretEvent = 1;
                break;
            case SDLK_SPACE: // On recommence le jeu avec la barre espace
                // score = 0;
                arretEvent = 1;
                *etat = 0;
                *debutTimer = time(NULL);
                b->x = WINDOWW / 2;
                b->y = WINDOWH / 2;
                b->v = 0;
                p->x = WINDOWW / 4;
                p->y = WINDOWH / 2;
                *score1 = 0;
                *score2 = 0;
                Mix_PlayMusic(musiqueJeu, 1);
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
    if (*score1 > *score2)
    {
        creationTexte("Le joueur 1 a gagne!", WINDOWW / 2, WINDOWH / 2, font, window, renderer);
    }
    else if (*score1 < *score2)
    {
        creationTexte("Le joueur 2 a gagne!", WINDOWW / 2, WINDOWH / 2, font, window, renderer);
    }
    else
    {
        creationTexte("Egalite!", WINDOWW / 2, WINDOWH / 2, font, window, renderer);
    }
}