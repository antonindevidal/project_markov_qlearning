#include "score.h"

void afficherScore(TTF_Font *font, SDL_Window *window, SDL_Renderer *renderer) {
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);

    SDL_Color couleur = {250, 0, 40, 255};
    SDL_Surface *texteScore = NULL;
    texteScore = TTF_RenderText_Blended(font, "Score: ", couleur);
    if (texteScore == NULL)
        endSDL(0, "Création du texte Score impossible", window, renderer);
    
    SDL_Texture *texteTexture = NULL;
    texteTexture = SDL_CreateTextureFromSurface(renderer, texteScore);
    if (texteTexture == NULL)
        endSDL(0, "Création texture impossible", window, renderer);
    SDL_FreeSurface(texteScore);

    SDL_Rect position = {0, 0, 0, 0};
    SDL_QueryTexture(texteTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texteTexture, NULL, &position);
    SDL_DestroyTexture(texteTexture);
}