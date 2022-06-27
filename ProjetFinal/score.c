#include "score.h"

void afficherScore(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer)
{
    /* Texte Score */
    creationTexte("Score: ", 20, WINDOWH - 60, font, window, renderer);

    /* Valeur du score */
    char scoreChar[10];
    sprintf(scoreChar, "%d", score);
    creationTexte(scoreChar, 270, WINDOWH - 60, font, window, renderer);
}
