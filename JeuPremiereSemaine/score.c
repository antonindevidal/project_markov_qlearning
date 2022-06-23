#include "score.h"

void creationTexte(char *texte, int posX, int posY, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer) {
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
    SDL_Color couleur = {250, 0, 40, 255};
    SDL_Surface *texteSurface = NULL;
    texteSurface = TTF_RenderText_Solid(font, texte, couleur);
    if (texteSurface == NULL)
        endSDL(0, "Création de la surface impossible", window, renderer);

    SDL_Texture *texteTexture = NULL;
    texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    if (texteTexture == NULL)
        endSDL(0, "Création texture impossible", window, renderer);
    SDL_FreeSurface(texteSurface);

    SDL_Rect position = {posX, posY, 0, 0};
    SDL_QueryTexture(texteTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texteTexture, NULL, &position);
    SDL_DestroyTexture(texteTexture);
}

void afficherScore(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer)
{
    /* Texte Score */
    creationTexte("Score: ", 20, WINDOWH-60, font, window, renderer);

    /* Valeur du score */
    char scoreChar[10];
    sprintf(scoreChar, "%d", score);
    creationTexte(scoreChar, 270, WINDOWH-60, font, window, renderer);
}

void texteFin(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer)
{
    creationTexte("GAME OVER", WINDOWW/2-180, WINDOWH/2-270, font, window, renderer);

    /*Score */
    creationTexte("Score: ", 245, WINDOWH/2-50, font, window, renderer);
    char scoreChar[10];
    sprintf(scoreChar, "%d", score);
    creationTexte(scoreChar, WINDOWW/2+75, WINDOWH/2-50, font, window, renderer);

    creationTexte("ESPACE - Rejouer", WINDOWW/2-300, WINDOWH/2+200, font, window, renderer);
}

void reset(listEnnemis_t* e,listB_t *b, player_t* player)
{
    liberationEnnemis(*e);
    *e = NULL;
    liberationBullets(*b);
    *b = NULL;
    player->y = WINDOWH /2;
    player->x = 100;

}