#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#define NBIMAGES 2
#define SOURCEX 1
#define SOURCEY 68
#define OFFSET 1
#define SPRITESIZE 16
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

// Update character position
void update(int *currentFrame, SDL_Rect *destination, SDL_Rect *source, SDL_Rect windowDimensions)
{
    //Move character 1 time per cycle
    *currentFrame = ((*currentFrame)+1)%2 ; // Change character sprite
    destination->x = (destination->x +5 ) %windowDimensions.w; //Change position on screen (with cycle)
    source->x = SOURCEX +  (SPRITESIZE + OFFSET) *(*currentFrame) ; // Change sprite postion in the spritesheet
}

// Draw character
void draw(SDL_Renderer *renderer, SDL_Texture *spritesheet, SDL_Rect *destination, SDL_Rect *source)
{

    SDL_RenderClear(renderer);            // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_RenderCopy(renderer, spritesheet, // Préparation de l'affichage
                   source,
                   destination);
    SDL_RenderPresent(renderer); // Affichage
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int currentFrame = 0;

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

    SDL_Texture *spritesheet;
    spritesheet = IMG_LoadTexture(renderer, "./Sprites/tilemap.png");
    if (spritesheet == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    float zoom = 2; // zoom, car ces images sont un peu petites

    source.x = SOURCEX;    // La première vignette est en début de ligne
    source.y = SOURCEY;    // On s'intéresse à la 4ème ligne, le bonhomme qui court
    source.w = SPRITESIZE; // Largeur de la vignette
    source.h = SPRITESIZE; // Hauteur de la vignette

    destination.w = SPRITESIZE * zoom; // Largeur du sprite à l'écran
    destination.h = SPRITESIZE * zoom; // Hauteur du sprite à l'écran

    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) / 2;

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    /*********************************************************************************************************************/
    /*             Cette partie pourrait avantageusement être remplacée par la boucle évènementielle                     */

    while (program_on)
    {
        SDL_FlushEvent(SDL_MOUSEMOTION);
        SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
        if (SDL_PollEvent(&event))
        {
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
        update(&currentFrame, &destination, &source,window_dimensions);
        draw(renderer, spritesheet, &destination, &source); // appel de la fonction qui crée l'image
        SDL_RenderPresent(renderer);                                               // affichage
        SDL_Delay(100);
    } 

    /* on referme proprement la SDL */
    SDL_DestroyTexture(spritesheet);
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}