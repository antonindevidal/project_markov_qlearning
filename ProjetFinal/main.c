#include <time.h>

#include "score.h"
#include "ball/ball.h"
#include "menus.h"
#include "player/player.h"

#include "terrain/terrain.h"
#include "screens/endScreen.h"
#include "renforcement/renforcement.h"

// int main(int argc, char **argv)
// {
// 	srand(time(0));
// 	(void)argc;
// 	(void)argv;
// 	int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = -1, cpt = 0;
// 	int debutTimer = 0;
// 	int score1 = 0, score2 = 0;
// 	enum EQUIPE e = EQUIPEDROITE;
// 	int etat = 1;

// 	SDL_bool programON = SDL_TRUE;
// 	SDL_Event event;

// 	SDL_Window *window = NULL;
// 	SDL_Renderer *renderer = NULL;

// 	SDL_DisplayMode screen;

// 	ball_t *ball = creationBall();
// 	if (ball == NULL)
// 	{
// 		endSDL(0, "ERROR CREATION BALL", window, renderer);
// 	}
// 	player_t *player = createPlayer(EQUIPEGAUCHE);
// 	if (player == NULL)
// 	{
// 		endSDL(0, "ERROR CREATION PLAYER", window, renderer);
// 	}

// 	/* Initialisation de la SDL  + gestion de l'échec possible */
// 	if (SDL_Init(SDL_INIT_VIDEO) != 0)
// 		endSDL(0, "ERROR SDL INIT", window, renderer);

// 	SDL_GetCurrentDisplayMode(0, &screen);

// 	/* Création de la fenêtre */
// 	window = SDL_CreateWindow("Nario Gréviste Ultimate",
// 							  SDL_WINDOWPOS_CENTERED,
// 							  SDL_WINDOWPOS_CENTERED,
// 							  WINDOWW,
// 							  WINDOWH,
// 							  SDL_WINDOW_OPENGL);
// 	if (window == NULL)
// 		endSDL(0, "ERROR WINDOW CREATION", window, renderer);

// 	/* Création du renderer */
// 	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
// 	if (renderer == NULL)
// 		endSDL(0, "ERROR RENDERER CREATION", window, renderer);

// 	/* Initialisation Font */
// 	if (TTF_Init() < 0)
// 		endSDL(0, "Erreur initialisation SDL TTF", window, renderer);

// 	TTF_Font *font = NULL;
// 	font = TTF_OpenFont("./resources/font/kenvector_future.ttf", 45);
// 	if (font == NULL)
// 		endSDL(0, "Erreur chargement Font", window, renderer);

// 	/* Création des textures */
// 	// A REMPLIR
// 	SDL_Texture *ballSprite = loadTextureFromImage("./resources/sprites/ball.png", window, renderer);
// 	SDL_Texture *playerSprite = loadTextureFromImage("./resources/sprites/player.png", window, renderer);
// 	SDL_Texture *terrainSpriteSheet = loadTextureFromImage("./resources/sprites/grass.png", window, renderer);
// 	SDL_Texture *mainTitle = loadTextureFromImage("./resources/TITLE.png", window, renderer);
// 	/* Boucle du jeu */
// 	while (programON)
// 	{ // Boucle événementielle du programme

// 		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
// 		SDL_RenderClear(renderer); // Effacer l'image précédente avant de dessiner la nouvelle

// 		SDL_FlushEvent(SDL_MOUSEMOTION);
// 		switch (etat)
// 		{
// 		case 0: // Etat: Jeu
// 			while (SDL_PollEvent(&event) && !arretEvent)
// 			{
// 				switch (event.type)
// 				{						   // En fonction de la valeur du type de cet évènement
// 				case SDL_QUIT:			   // Un évènement simple, on a cliqué sur la x de la fenêtre
// 					programON = SDL_FALSE; // Il est temps d'arrêter le programme
// 					arretEvent = 1;
// 					break;
// 				case SDL_KEYDOWN:
// 					switch (event.key.keysym.sym)
// 					{
// 					case SDLK_ESCAPE:
// 						programON = SDL_FALSE; // Fermeture du programme à l'appuie sur la touche ECHAP
// 						arretEvent = 1;
// 						break;
// 					case SDLK_z:
// 						movePlayer(player, HAUTD);
// 						arretEvent = 1;
// 						break;
// 					case SDLK_q:
// 						movePlayer(player, GAUCHED);
// 						arretEvent = 1;
// 						break;
// 					case SDLK_s:
// 						movePlayer(player, BASD);
// 						arretEvent = 1;
// 						break;
// 					case SDLK_d:
// 						movePlayer(player, DROITD);
// 						arretEvent = 1;
// 						break;
// 					default:
// 						break;
// 					}
// 					break;
// 				case SDL_MOUSEBUTTONDOWN:
// 					if ((SDL_GetMouseState(&mouseX, &mouseY) &
// 						 SDL_BUTTON(SDL_BUTTON_LEFT)))
// 					{ // Si c'est un click gauche
// 						pushBall(ball, rand() % 360, BALL_ACCELERATION);
// 					}
// 					arretEvent = 1;
// 					break;
// 				default: // L'évènement défilé ne nous intéresse pas
// 					break;
// 				}
// 			}
// 			arretEvent = 0;
// 			cycles++;

// 			/* Update cycle */
// 			// A REMPLIR
// 			if (moveBall(ball, &e))
// 			{
// 				if (e == EQUIPEGAUCHE)
// 					score1++;
// 				if (e == EQUIPEDROITE)
// 					score2++;

// 				ball->x = WINDOWW / 2;
// 				ball->y = WINDOWH / 2;
// 				ball->v = 0;
// 				player->x = WINDOWW / 4;
// 				player->y = WINDOWH / 2;
// 			}
// 			playerBallCollision(player, ball);
// 			if ((int)(time(NULL) - debutTimer) >= TIMEGAME)
// 			{
// 				etat = 2;
// 			}

// 			/* Draw frame */
// 			afficherTerrain(terrainSpriteSheet, renderer);
// 			afficherTexture(ballSprite, renderer, ball->size, ball->size, ball->x, ball->y);
// 			afficherTexture(playerSprite, renderer, player->w, player->h, player->x, player->y);
// 			afficherScore(score1, score2, font, window, renderer);
// 			char t[10];
// 			int min = (TIMEGAME - (int)(time(NULL) - debutTimer)) / 60;
// 			int sec = (TIMEGAME - (int)(time(NULL) - debutTimer)) % 60;
// 			sprintf(t, "%d : %d", min, sec);
// 			creationTexte(t, WINDOWW / 2, 50, font, window, renderer);

// 			// printf("%d %d %d %d\n", ball->x, ball->y, ball->vx,ball->vy);
// 			break;
// 		case 1: // Etat: Ecran tittre
// 			while (SDL_PollEvent(&event) && !arretEvent)
// 			{
// 				switch (event.type)
// 				{			   // En fonction de la valeur du type de cet évènement
// 				case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la fenêtre
// 					programON = SDL_FALSE;
// 					arretEvent = 1;
// 					break;
// 				case SDL_KEYDOWN:
// 					switch (event.key.keysym.sym)
// 					{
// 					case SDLK_ESCAPE:
// 						programON = SDL_FALSE;
// 						arretEvent = 1;
// 						break;
// 					case SDLK_SPACE:
// 						arretEvent = 1;
// 						etat = 0;
// 						debutTimer = time(NULL);
// 						break;
// 					default:
// 						break;
// 					}
// 					break;
// 				default:
// 					break;
// 				}
// 			}
// 			arretEvent = 0;
// 			// Draw Frame
// 			cpt++;
// 			afficherTexture(mainTitle, renderer, 600, 300, WINDOWW / 2, (WINDOWH / 2) + cos(cpt * 0.05) * 20 - 10);
// 			if (cpt % 80 < 40)
// 			{
// 				creationTexte("Press space to start", WINDOWW / 2, 3.5 * (WINDOWH / 4), font, window, renderer);
// 			}
// 			break;
// 		case 2: // Etat: Fin
// 			ecranFin(window,font,renderer,event,&score1,&score2,player,ball,&debutTimer,&etat,&programON);
// 			break;
// 		default:
// 			break;
// 		}
// 		SDL_Delay(20);
// 		SDL_RenderPresent(renderer); // affichage
// 	}
// 	TTF_CloseFont(font);
// 	endSDL(1, "Normal ending", window, renderer);
// 	TTF_Quit();
// 	IMG_Quit();
// 	SDL_Quit();
// 	return EXIT_SUCCESS;
// }

//main renforcement
int main(){
	ordinateur_t *ordi1;
	ordinateur_t *ordi2;
	ordi1=creerOrdi(EQUIPEGAUCHE);
	ordi2=creerOrdi(EQUIPEDROITE);
	initQTableOrdi(ordi1);
	initQTableOrdi(ordi2);
	//afficherQTable(ordi1);
	//afficherQTable(ordi2);
	renforcement(ordi1,ordi2);
	libererOrdi(ordi1);
	libererOrdi(ordi2);
	printf("-----------------FIN--------------\n");
	return 0;
}