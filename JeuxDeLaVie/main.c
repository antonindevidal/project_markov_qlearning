#include "affichage.h"
#include "cycle.h"
#include "save.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#define WINDOWH 400
#define WINDOWW 500
#define CELLSIZE 10
#define NBCYCLES 20

void end_sdl(char ok,			 // fin normale : ok = 0 ; anormale ok = 1
			 char const *msg,	 // message à afficher
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
	{								   // Destruction si nécessaire du renderer
		SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
		renderer = NULL;
	}
	if (window != NULL)
	{							   // Destruction si nécessaire de la fenêtre
		SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
		window = NULL;
	}

	SDL_Quit();

	if (!ok)
	{ // On quitte si cela ne va pas
		exit(EXIT_FAILURE);
	}
}

// Create grid: return 0 if no errors
int **creationGrille(int *error, int tailleX, int tailleY)
{
	int **nouv;
	nouv = malloc(sizeof(int *) * tailleY);
	if (nouv != NULL)
	{
		for (int i = 0; i < tailleY; i++)
		{
			nouv[i] = malloc(sizeof(int *) * tailleX);
			if (nouv == NULL)
			{
				*error = 1;
			}
			else
			{
				for (int j = 0; j < tailleX; j++)
				{
					nouv[i][j] = 0;
				}
			}
		}
	}
	else
	{
		*error = 1;
	}
	return nouv;
}
void libererGrille(int **tab, int tailleY)
{
	for (int i = 0; i < tailleY; i++)
	{
		free(tab[i]);
	}
	free(tab);
}

void poserCase(int caseX, int caseY, int **nouv, int tailleX, int tailleY)
{
	if (caseX < tailleX && caseY < tailleY)
	{
		nouv[caseY][caseX] = !nouv[caseY][caseX];
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int mouseX = 0, mouseY = 0, arretEvent = 0, cycles = 0,pause = 0;
	int **nouv = NULL, **anc = NULL, erreur = 0;

	int tailleX = WINDOWW / CELLSIZE;
	int tailleY = WINDOWH / CELLSIZE;

	SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
	SDL_Event event;				// c'est le type IMPORTANT !!

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_DisplayMode screen;

	/*********************************************************************************************************************/
	/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		end_sdl(0, "ERROR SDL INIT", window, renderer);

	SDL_GetCurrentDisplayMode(0, &screen);

	nouv = creationGrille(&erreur, tailleX, tailleY);
	if (erreur)
		end_sdl(0, "ERROR INIT GRILLE", window, renderer);

	anc = creationGrille(&erreur, tailleX, tailleY);
	if (erreur)
		end_sdl(0, "ERROR INIT GRILLE", window, renderer);

	anc[10][11] = 1;
	anc[11][12] = 1;
	anc[12][10] = 1;
	anc[12][11] = 1;
	anc[12][12] = 1;

	/* Création de la fenêtre */
	window = SDL_CreateWindow("Premier dessin",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WINDOWW,
							  WINDOWH,
							  SDL_WINDOW_OPENGL);
	if (window == NULL)
		end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	/* Création du renderer */
	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

	while (program_on)
	{
		SDL_FlushEvent(SDL_MOUSEMOTION);
		while (SDL_PollEvent(&event) && !arretEvent)
		{
			switch (event.type)
			{							// En fonction de la valeur du type de cet évènement
			case SDL_QUIT:				// Un évènement simple, on a cliqué sur la x de la fenêtre
				program_on = SDL_FALSE; // Il est temps d'arrêter le programme
				arretEvent = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					program_on = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
					arretEvent = 1;
					break;
				case SDLK_s:
					saveConfig("config.txt", nouv, tailleX, tailleY);
					break;

				case SDLK_c:
					chargerConfig("config.txt", anc, &tailleX, &tailleY);
					break;
				case SDLK_SPACE:
					pause = !pause;
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (SDL_GetMouseState(&mouseX, &mouseY) &
					SDL_BUTTON(SDL_BUTTON_LEFT))
				{																			// Si c'est un click gauche
					poserCase(mouseX / CELLSIZE, mouseY / CELLSIZE, anc, tailleX, tailleY); // Fonction à éxécuter lors d'un click gauche
				}
				else if (SDL_GetMouseState(NULL, NULL) &
						 SDL_BUTTON(SDL_BUTTON_RIGHT))
				{ // Si c'est un click droit
					poserCase(mouseX / CELLSIZE, mouseY / CELLSIZE, anc, tailleX, tailleY);
					// Fonction à éxécuter lors d'un click droit
				}
				arretEvent = 1;
				break;
			default: // L'évènement défilé ne nous intéresse pas
				break;
			}
		}
		cycles++;
		arretEvent = 0;
		SDL_Delay(16);
		afficherGrille(anc, tailleX, tailleY, CELLSIZE, renderer);

		// Update cycle
		if (cycles >= NBCYCLES && !pause)
		{
			cycles = 0;
			cycle(nouv, anc, tailleX, tailleY, 1);
            detection_etat_stable(anc, nouv, tailleX, tailleY);
			int **tmp = anc;
			anc = nouv;
			nouv = tmp;
		}

		// Draw Frame

		SDL_RenderPresent(renderer); // affichage
	}

	libererGrille(nouv, tailleY);
	libererGrille(anc, tailleY);

	end_sdl(1, "Normal ending", window, renderer);
	SDL_Quit();
	return EXIT_SUCCESS;
}