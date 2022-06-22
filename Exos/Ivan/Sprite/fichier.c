#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#define NBIMAGES 8
#define SOURCEX 0
#define SOURCEY 0
#define OFFSET 0
#define SPRITESIZEX 231
#define SPRITESIZEY 190
/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{
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

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre

    SDL_RenderCopy(renderer, my_texture,
                   &source,
                   &destination);                 // Création de l'élément à afficher
    SDL_RenderPresent(renderer);                  // Affichage

    SDL_RenderClear(renderer);                    // Effacer la fenêtre */
}

int nbActuel = 0;
int j = 0;
int etape[24] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7};
// Update character position
void
update(int *currentFrame, SDL_Rect *destination, SDL_Rect *source, SDL_Rect windowDimensions)
{
    // Move character 1 time per cycle
    if (*currentFrame < 25)
    {
        (*currentFrame)++; //((*currentFrame)+1)%NBIMAGES ; // Change character sprite
        destination->x = (destination->x + 14) % windowDimensions.w;         // Change position on screen (with cycle)
        source->x = SOURCEX + (SPRITESIZEX + OFFSET) * etape[*currentFrame]; // Change sprite postion in the spritesheet
    }
    else
    {
        j++;
        if (j >= 7)
        {
            j = 0;
        }
        source->x = SOURCEX + (SPRITESIZEX + OFFSET) * j;
    }
}

// Draw character
void draw(SDL_Renderer *renderer, SDL_Texture *spritesheet, SDL_Rect *destination, SDL_Rect *source, SDL_Texture **tab, SDL_Rect *bg, SDL_Rect *bgSize)
{

    SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle
    for (int i = 0; i < 5; i++)
    {
        SDL_RenderCopy(renderer, tab[i], bgSize, bg);
    }

    SDL_RenderCopy(renderer, spritesheet, // Préparation de l'affichage
                   source, destination);

    SDL_RenderCopy(renderer, tab[5], bgSize, bg);
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
    /*                         InitialisationSDL_RenderCopy(renderer, tab[i], bgSize, bg); de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.66, screen.h * 0.66, SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    SDL_Texture *spritesheet;
    spritesheet = IMG_LoadTexture(renderer, "./Sprites/Run.png");
    if (spritesheet == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesheet2;
    spritesheet2 = IMG_LoadTexture(renderer, "./Sprites/Attack1.png");
    if (spritesheet2 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesheetHill;
    spritesheetHill = IMG_LoadTexture(renderer, "./Sprites/Hills01.png");
    if (spritesheetHill == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesbg2;
    spritesbg2 = IMG_LoadTexture(renderer, "./Sprites/Hills02.png");
    if (spritesbg2 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesbg3;
    spritesbg3 = IMG_LoadTexture(renderer, "./Sprites/Hills03.png");
    if (spritesbg3 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesbg4;
    spritesbg4 = IMG_LoadTexture(renderer, "./Sprites/Hills04.png");
    if (spritesbg4 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesbg5;
    spritesbg5 = IMG_LoadTexture(renderer, "./Sprites/Hills05.png");
    if (spritesbg5 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *spritesbg6;
    spritesbg6 = IMG_LoadTexture(renderer, "./Sprites/Hills06.png");
    if (spritesbg6 == NULL)
        end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_Texture *tab[7] = {spritesheetHill, spritesbg2, spritesbg3, spritesbg4, spritesbg5, spritesbg6};

    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_Rect bg = {0}, bgSize = {0};
    bg.x = 0;
    bg.y = 0;
    bg.h = screen.h * 0.66;
    bg.w = screen.w * 0.66;

    bgSize.x = 0;
    bgSize.y = 0;
    bgSize.w = 512;
    bgSize.h = 256;

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    float zoom = 1; // zoom, car ces images sont un peu petites

    source.x = SOURCEX;     // La première vignette est en début de ligne
    source.y = SOURCEY;     // On s'intéresse à la 4ème ligne, le bonhomme qui court
    source.w = SPRITESIZEX; // Largeur de la vignette
    source.h = SPRITESIZEY; // Hauteur de la vignette

    destination.w = SPRITESIZEX * zoom; // Largeur du sprite à l'écran
    destination.h = SPRITESIZEY * zoom; // Hauteur du sprite à l'écran
    destination.x = 200;
    destination.y = screen.h * 0.66 * 0.75; // La course se fait en milieu d'écran (en vertical)

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
        play_with_texture_1(spritesheetHill, window, renderer);
        update(&currentFrame, &destination, &source, window_dimensions);
        if (currentFrame < 25)
        {
            draw(renderer, spritesheet, &destination, &source, tab, &bg, &bgSize); // appel de la fonction qui crée l'image
        }
        else
        {
            draw(renderer, spritesheet2, &destination, &source, tab, &bg, &bgSize); // appel de la fonction qui crée l'image
        }

        SDL_RenderPresent(renderer); // affichage
        SDL_Delay(100);
    }

    /* on referme proprement la SDL */
    SDL_DestroyTexture(spritesheet);
    SDL_DestroyTexture(spritesheet2);
    SDL_DestroyTexture(spritesheetHill);
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}