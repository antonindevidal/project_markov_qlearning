#include <SDL2/SDL.h>
#include <stdio.h>

#define NBFENETRES 4
#define FENETRE_W 400
#define FENETRE_H 300

void end_sdl(char ok,			   // fin normale : ok = 0 ; anormale ok = 1
			 char const *msg,	   // message à afficher
			 SDL_Window **windows) // fenêtres à fermer)
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

	for (int i = 0; i < NBFENETRES; i++)
	{
		if (windows[i] != NULL)
		{								   // Destruction si nécessaire de la fenêtre
			SDL_DestroyWindow(windows[i]); // Attention : on suppose que les NULL sont maintenus !!
			windows[i] = NULL;
		}
	}

	SDL_Quit();

	if (!ok)
	{ // On quitte si cela ne va pas
		exit(EXIT_FAILURE);
	}
}

SDL_bool update(SDL_Window **windows, SDL_DisplayMode screen)
{
	SDL_bool on = SDL_TRUE;
	int x = 0, y = 0, w = 0, h = 0;
	for (int i = 0; i < NBFENETRES; i++)
	{
		SDL_GetWindowPosition(windows[i], &x, &y);
		if (x != (screen.w / 2) - FENETRE_W / 2 || y != (screen.h / 2) - FENETRE_H / 2)
		{
			if (x > (screen.w / 2) - FENETRE_W / 2)
			{
				x--;
			}
			else if (x < (screen.w / 2) - FENETRE_W / 2)
			{
				x++;
			}

			if (y > (screen.h / 2) - FENETRE_H / 2)
			{
				y--;
			}
			else if (y < (screen.h / 2) - FENETRE_H / 2)
			{
				y++;
			}
		}
		else
		{
			SDL_GetWindowSize(windows[i],&w,&h);
			if (w <600){
				w+=5;
				h+=5;
			}else 
			{	
				on = SDL_FALSE;
			}
			
			SDL_SetWindowSize(windows[i],w,h);
		}

		SDL_SetWindowPosition(windows[i], x, y);
	}
	return on;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
	SDL_Event event;				// c'est le type IMPORTANT !!

	SDL_Window
		**windows = malloc(NBFENETRES * sizeof(SDL_Window *));
	if (windows == NULL)
	{
		SDL_Log("ERREUR MALLOC TABLEAU DE FENETRE");
		exit(EXIT_FAILURE);
	}

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

	for (int i = 0; i < NBFENETRES; i++)
	{

		int posX = 0, posY = 0;
		if (i % 2 == 1)
		{
			posX = screen.w - FENETRE_W;
		}
		if (i / 2 > 0)
		{
			posY = screen.h - FENETRE_H;
		}
		/* Création de la fenêtre de gauche */
		windows[i] = SDL_CreateWindow(
			"Fenêtre",			   // codage en utf8, donc accents possibles
			posX, posY,			   // coin haut gauche en haut gauche de l'écran
			FENETRE_W, FENETRE_H,  // largeur = 400, hauteur = 300
			SDL_WINDOW_RESIZABLE); // redimensionnable

		if (windows[i] == NULL)
		{
			end_sdl(0, "ERROR WINDOW CREATION", windows);
		}
	}

	int yOffset = 0; // Y value of getWindowPosition return position at the bottom of the header of the window
	SDL_GetWindowPosition(windows[0], NULL, &yOffset);

	while (program_on)
	{
		program_on = update(windows, screen);
		if (SDL_PollEvent(&event))
		{ // si la file d'évènements n'est pas vide : défiler l'élément en tête
		  // de file dans 'event'
			switch (event.type)
			{							// En fonction de la valeur du type de cet évènement
			case SDL_QUIT:				// Un évènement simple, on a cliqué sur la x de la fenêtre
				program_on = SDL_FALSE; // Il est temps d'arrêter le programme
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					program_on = SDL_FALSE;
					break;

				default:
					break;
				}

			default: // L'évènement défilé ne nous intéresse pas
				break;
			}
		}
		SDL_Delay(1);
	}

	/* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
	for (int i = 0; i < NBFENETRES; i++)
	{
		SDL_DestroyWindow(windows[i]); // la fenêtre 1
	}

	SDL_Quit(); // la SDL

	return 0;
}