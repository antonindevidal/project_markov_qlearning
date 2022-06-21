#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

int balleX = 340;
int balleY = 360;
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

void draw(SDL_Renderer *renderer, SDL_bool AnimationFini)
{
    if (!AnimationFini)
    {
        SDL_Rect rectangle;

        SDL_SetRenderDrawColor(renderer,
                               255, 102, 170, // mode Red, Green, Blue (tous entre 0..255)
                               255);          // 0 = transparent ; 255 = opaque
        rectangle.x = 0;                      // x haut gauche du rectangle
        rectangle.y = 0;                      // y haut gauche du rectangle
        rectangle.w = 1720;                   // sa largeur (w = width)
        rectangle.h = 1080;                   // sa hauteur (h = height)

        SDL_RenderFillRect(renderer, &rectangle);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
        for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
        {
            SDL_RenderDrawPoint(renderer,
                                300 + 30 * cos(angle),  // coordonnée en x
                                300 + 30 * sin(angle)); //            en y
        }

        SDL_RenderDrawLine(renderer, 300, 330, 300, 430); // xi,yi;xj,yj
        SDL_RenderDrawLine(renderer, 300, 430, 260, 480); // jambe gauche
        SDL_RenderDrawLine(renderer, 300, 430, 340, 480); // jambe droite
        SDL_RenderDrawLine(renderer, 300, 350, 315, 390); // bras
        SDL_RenderDrawLine(renderer, 315, 390, 340, 360); // avant-bras

        SDL_Rect rect;
        rect.x = 900; // x haut gauche du rectangle
        rect.y = 250; // y haut gauche du rectangle
        rect.w = 30;  // sa largeur (w = width)
        rect.h = 250; // sa hauteur (h = height)
        SDL_RenderDrawRect(renderer, &rect);

        // balle
        for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
        {
            SDL_RenderDrawPoint(renderer, balleX + 25 * cos(angle), balleY + 25 * sin(angle));
        }
    }
    else
    {
                SDL_Rect rectangle;

        SDL_SetRenderDrawColor(renderer,
                               150, 150, 150, // mode Red, Green, Blue (tous entre 0..255)
                               255);          // 0 = transparent ; 255 = opaque
        rectangle.x = 0;                      // x haut gauche du rectangle
        rectangle.y = 0;                      // y haut gauche du rectangle
        rectangle.w = 1720;                   // sa largeur (w = width)
        rectangle.h = 1080;                   // sa hauteur (h = height)

        SDL_RenderFillRect(renderer, &rectangle);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
        for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
        {
            SDL_RenderDrawPoint(renderer,
                                190 + 30 * cos(angle),  // coordonnée en x
                                450 + 30 * sin(angle)); //            en y
        }

        SDL_RenderDrawLine(renderer, 215, 465, 300, 465); // xi,yi;xj,yj
        SDL_RenderDrawLine(renderer, 300, 465, 340, 450); // jambe gauche
        SDL_RenderDrawLine(renderer, 300, 465, 340, 480); // jambe droite
        SDL_RenderDrawLine(renderer, 235, 465, 190, 515); // bras droit
        SDL_RenderDrawLine(renderer, 235, 465, 200, 410); // bras gauche

        SDL_Rect rect;
        rect.x = 900; // x haut gauche du rectangle
        rect.y = 250; // y haut gauche du rectangle
        rect.w = 30;  // sa largeur (w = width)
        rect.h = 250; // sa hauteur (h = height)
        SDL_RenderDrawRect(renderer, &rect);

        // balle
        for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
        {
            SDL_RenderDrawPoint(renderer, 360 + 25 * cos(angle), 450 + 25 * sin(angle));
        }
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int directionBalle = 1;
    SDL_bool AnimationFini = SDL_FALSE;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // Evènement à traiter

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/

    while (program_on)
    { // La boucle des évènements
        if (SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
          // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: // Le type de event est : une touche appuyée
                              // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                              // l'event, plusieurs champs deviennent pertinents
                switch (event.key.keysym.sym)
                {                   // la touche appuyée est ...
                case SDLK_ESCAPE:   // 'ESCAPE'
                    program_on = 0; // 'escape' ou 'q', d'autres façons de quitter le programme
                    break;

                default: // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            }
            draw(renderer, AnimationFini); // appel de la fonction qui crée l'image

            balleX = balleX + directionBalle * 5;
            if (balleX > 874)
                directionBalle = -1;
            if (balleX < 300)
                AnimationFini = SDL_TRUE;

            SDL_RenderPresent(renderer); // affichage
            SDL_Delay(10);               // Pause exprimée en ms
        }
    }

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);

    SDL_Quit(); // la SDL
    return EXIT_SUCCESS;
}