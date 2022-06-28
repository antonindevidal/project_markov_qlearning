#include <time.h>

#include "score.h"
#include "ball/ball.h"
#include "menus.h"
#include "player/player.h"
#include "terrain/terrain.h"

int main(int argc, char **argv)
{
	srand(time(0));
	(void)argc;
	(void)argv;
	int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = -1;
	int score1 = 0, score2 = 0;
	enum EQUIPE e = EQUIPEDROITE;
	int etat = 1;

	SDL_bool programON = SDL_TRUE;
	SDL_Event event;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_DisplayMode screen;

	ball_t *ball = creationBall();
	if (ball == NULL)
	{
		endSDL(0, "ERROR CREATION BALL", window, renderer);
	}
	player_t *player = createPlayer(EQUIPEGAUCHE);
	if (player == NULL)
	{
		endSDL(0, "ERROR CREATION PLAYER", window, renderer);
	}

	/* Initialisation de la SDL  + gestion de l'échec possible */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		endSDL(0, "ERROR SDL INIT", window, renderer);

	SDL_GetCurrentDisplayMode(0, &screen);

	/* Création de la fenêtre */
	window = SDL_CreateWindow("Nario Gréviste Ultimate",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WINDOWW,
							  WINDOWH,
							  SDL_WINDOW_OPENGL);
	if (window == NULL)
		endSDL(0, "ERROR WINDOW CREATION", window, renderer);

	/* Création du renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		endSDL(0, "ERROR RENDERER CREATION", window, renderer);

	/* Initialisation Font */
	if (TTF_Init() < 0)
		endSDL(0, "Erreur initialisation SDL TTF", window, renderer);

	TTF_Font *font = NULL;
	font = TTF_OpenFont("./resources/font/kenvector_future.ttf", 45);
	if (font == NULL)
		endSDL(0, "Erreur chargement Font", window, renderer);

	/* Création des textures */
	// A REMPLIR
	SDL_Texture *ballSprite = loadTextureFromImage("./resources/sprites/ball.png", window, renderer);
	SDL_Texture *playerSprite = loadTextureFromImage("./resources/sprites/player.png", window, renderer);
	SDL_Texture *terrainSpriteSheet = loadTextureFromImage("./resources/sprites/grass.png", window, renderer);
	SDL_Texture *mainTitle = loadTextureFromImage("./resources/TITLE.png", window, renderer);

	/* Boucle du jeu */
	while (programON)
	{ // Boucle événementielle du programme

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle

		SDL_FlushEvent(SDL_MOUSEMOTION);
		switch (etat)
		{
		case 0: // Etat: Jeu
			while (SDL_PollEvent(&event) && !arretEvent)
			{
				switch (event.type)
				{						   // En fonction de la valeur du type de cet évènement
				case SDL_QUIT:			   // Un évènement simple, on a cliqué sur la x de la fenêtre
					programON = SDL_FALSE; // Il est temps d'arrêter le programme
					arretEvent = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						programON = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
						arretEvent = 1;
						break;
					case SDLK_z:
						movePlayer(player, HAUTD);
						arretEvent = 1;
						break;
					case SDLK_q:
						movePlayer(player, GAUCHED);
						arretEvent = 1;
						break;
					case SDLK_s:
						movePlayer(player, BASD);
						arretEvent = 1;
						break;
					case SDLK_d:
						movePlayer(player, DROITD);
						arretEvent = 1;
						break;
					default:
						break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if ((SDL_GetMouseState(&mouseX, &mouseY) &
						 SDL_BUTTON(SDL_BUTTON_LEFT)))
					{ // Si c'est un click gauche
						pushBall(ball, rand() % 360);
					}
					arretEvent = 1;
					break;
				default: // L'évènement défilé ne nous intéresse pas
					break;
				}
			}
			arretEvent = 0;
			cycles++;

			/* Update cycle */
			// A REMPLIR
			if (moveBall(ball, &e))
			{
				if (e == EQUIPEGAUCHE)
					score1++;
				if (e == EQUIPEDROITE)
					score2++;

				ball->x = WINDOWW / 2;
				ball->y = WINDOWH / 2;
				ball->v = 0;
				player->x = WINDOWW / 4;
				player->y = WINDOWH / 2;
			}
			playerBallCollision(player, ball);

			/* Draw frame */
			afficherTerrain(terrainSpriteSheet, renderer);
			afficherTexture(ballSprite, renderer, ball->size, ball->size, ball->x, ball->y);
			afficherTexture(playerSprite, renderer, player->w, player->h, player->x, player->y);
			afficherScore(score1, score2, font, window, renderer);
			// printf("%d %d %d %d\n", ball->x, ball->y, ball->vx,ball->vy);
			break;
		case 1: // Etat: Ecran tittre
			while (SDL_PollEvent(&event) && !arretEvent)
			{
				switch (event.type)
				{			   // En fonction de la valeur du type de cet évènement
				case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la fenêtre
					programON = SDL_FALSE;
					arretEvent = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						programON = SDL_FALSE;
						arretEvent = 1;
						break;
					case SDLK_SPACE:
						arretEvent = 1;
						etat = 0;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			arretEvent = 0;
			// Draw Frame
			afficherTexture(mainTitle, renderer, 800, 300, WINDOWW / 2, WINDOWH / 2);

			break;
		case 2: // Etat: Fin
			while (SDL_PollEvent(&event) && !arretEvent)
			{
				switch (event.type)
				{			   // En fonction de la valeur du type de cet évènement
				case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la fenêtre
					programON = SDL_FALSE;
					arretEvent = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						programON = SDL_FALSE;
						arretEvent = 1;
						break;
					case SDLK_SPACE: // On recommence le jeu avec la barre espace
						// score = 0;
						arretEvent = 1;
						etat = 0;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			arretEvent = 0;
			// Draw Frame
			break;
		default:
			break;
		}
		SDL_Delay(20);
		SDL_RenderPresent(renderer); // affichage
	}

	TTF_CloseFont(font);
	endSDL(1, "Normal ending", window, renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
