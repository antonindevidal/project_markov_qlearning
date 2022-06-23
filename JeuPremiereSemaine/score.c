#include "score.h"

void afficherScore(int score, TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer) {
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);

    SDL_Color couleur = {250, 0, 40, 255};
    SDL_Surface *texteScore = NULL;
    texteScore = TTF_RenderText_Solid(font, "Score: ", couleur);
    if (texteScore == NULL)
        endSDL(0, "Création du texte Score impossible", window, renderer);
    
    char scoreChar[10];
    sprintf(scoreChar, "%d", score);
    SDL_Surface *scoreAct = NULL;
    scoreAct = TTF_RenderText_Solid(font, scoreChar, couleur);
    if (scoreAct == NULL)
        endSDL(0, "Création du texte Score impossible", window, renderer);

    /* Texte Score */
    SDL_Texture *texteTexture = NULL;
    texteTexture = SDL_CreateTextureFromSurface(renderer, texteScore);
    if (texteTexture == NULL)
        endSDL(0, "Création texture impossible", window, renderer);
    SDL_FreeSurface(texteScore);

    SDL_Rect position = {20, WINDOWH-60, 0, 0};
    SDL_QueryTexture(texteTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texteTexture, NULL, &position);
    SDL_DestroyTexture(texteTexture);

    /* Valeur du score */
    SDL_Texture *texteTexture2 = NULL;
    texteTexture2 = SDL_CreateTextureFromSurface(renderer, scoreAct);
    if (texteTexture2 == NULL)
        endSDL(0, "Création texture impossible", window, renderer);
    SDL_FreeSurface(scoreAct);

    SDL_Rect position2 = {270, WINDOWH-60, 0, 0};
    SDL_QueryTexture(texteTexture2, NULL, NULL, &position2.w, &position2.h);
    SDL_RenderCopy(renderer, texteTexture2, NULL, &position2);
    SDL_DestroyTexture(texteTexture2);
}