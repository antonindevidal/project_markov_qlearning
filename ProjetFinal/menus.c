#include "menus.h"

void menuDebut(TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer) {
    creationTexte("Nario Gréviste Ultimate", WINDOWW / 2 - 180, WINDOWH / 2 - 270, font, window, renderer);
}

void menuFin(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer)
{
    creationTexte("GAME OVER", WINDOWW / 2 - 180, WINDOWH / 2 - 270, font, window, renderer);

    /*Score */
    creationTexte("Score: ", 400, WINDOWH / 2 - 50, font, window, renderer);
    char scoreChar[10];
    sprintf(scoreChar, "%d", score);
    creationTexte(scoreChar, WINDOWW / 2 + 75, WINDOWH / 2 - 50, font, window, renderer);

    creationTexte("ESPACE - Rejouer", WINDOWW / 2 - 300, WINDOWH / 2 + 200, font, window, renderer);
}