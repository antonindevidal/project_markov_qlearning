#include <SDL2/SDL.h>
#include <stdio.h>


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
  {                                // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)
  {                            // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
    window = NULL;
  }

  SDL_Quit();

  if (!ok)
  { // On quitte si cela ne va pas
    exit(EXIT_FAILURE);
  }
}
void draw(SDL_Renderer *renderer)
{
  SDL_Rect rectangle;

  SDL_SetRenderDrawColor(renderer,
                         50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                         255);     // 0 = transparent ; 255 = opaque
  rectangle.x = 0;                 // x haut gauche du rectangle
  rectangle.y = 0;                 // y haut gauche du rectangle
  rectangle.w = 400;               // sa largeur (w = width)
  rectangle.h = 400;               // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  SDL_Window
      *window = NULL; // Future fenêtre de droite
  SDL_Renderer *renderer = NULL;

  SDL_DisplayMode screen;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError()); // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }
  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n",
         screen.w, screen.h);

  /* Création de la fenêtre de gauche */
  window = SDL_CreateWindow(
      "Fenêtre à gauche",    // codage en utf8, donc accents possibles
      0, 0,                  // coin haut gauche en haut gauche de l'écran
      400, 300,              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE); // redimensionnable

  if (window == NULL)
  {
    end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
  }
  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  draw(renderer); // appel de la fonction qui crée l'image
  SDL_RenderPresent(renderer);

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(2000); // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window); // la fenêtre 1

  SDL_Quit(); // la SDL

  return 0;
}