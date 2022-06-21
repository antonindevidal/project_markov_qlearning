#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define HAUTEUR_BRAS_MAX 250
#define HAUTEUR_BRAS_MIN 450

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
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

//Update character position
void update(int *hauteurBras, int *montee)
{
    if (*hauteurBras < HAUTEUR_BRAS_MAX) //600
    {
        *montee = 0;
    }
    else if (*hauteurBras > HAUTEUR_BRAS_MIN) //250
    {
        *montee = 1;
    }

    if (*montee)
    {
        *hauteurBras -= 5;
    }
    else
    {
        *hauteurBras += 5;
    }
}

//Draw character
void draw(SDL_Renderer *renderer, SDL_DisplayMode screen, int hauteurBras)
{
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer,
                           255, 255, 255, // mode Red, Green, Blue (tous dans 0..255)
                           255);          // 0 = transparent ; 255 = opaque
    rectangle.x = 0;                      // x haut gauche du rectangle
    rectangle.y = 0;                      // y haut gauche du rectangle
    rectangle.w = screen.w;               // sa largeur (w = width)
    rectangle.h = screen.h;               // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
    SDL_SetRenderDrawColor(renderer,
                           0, // quantité de Rouge
                           0, //          de vert
                           0, //          de bleu
                           255);
    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
    {
        // opacité = opaque
        SDL_RenderDrawPoint(renderer,
                            200 + 100 * cos(angle),  // coordonnée en x
                            200 + 100 * sin(angle)); //            en y
    }

    SDL_RenderDrawLine(renderer,
                       200, 300,  // x,y du point de la première extrémité
                       200, 450); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       200, 450,  // x,y du point de la première extrémité
                       150, 550); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       200, 450,  // x,y du point de la première extrémité
                       250, 550); // x,y seconde extrémité

    SDL_RenderDrawLine(renderer,
                       200, 350,          // x,y du point de la première extrémité
                       350, hauteurBras); // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                       200, 350, // x,y du point de la première extrémité
                       50, 250); // x,y seconde extrémité
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int hauteurBras = 300, montee = 1;

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    /*********************************************************************************************************************/
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
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
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */

    while (program_on)
    {
        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    program_on = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
                    break;

                default:
                    break;
                }

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        update(&hauteurBras, &montee);
        draw(renderer, screen, hauteurBras); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);         // affichage

        SDL_Delay(10);
    } // Pause exprimée en ms

    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}