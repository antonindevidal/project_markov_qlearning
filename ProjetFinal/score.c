#include "score.h"

void afficherScore(int score1,int score2, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer)
{
    char scoreChar[10];
    sprintf(scoreChar, "%d", score1);
    creationTexte(scoreChar, WINDOWW/4, 10, font, window, renderer);

    sprintf(scoreChar, "%d", score2);
    creationTexte(scoreChar, (WINDOWW/4)*3, 10, font, window, renderer);
}
