#include <time.h>

#include "score.h"
#include "ball/ball.h"
#include "menus.h"
#include "player/player.h"

#include "terrain/terrain.h"
#include "screens/endScreen.h"
#include "renforcement/renforcement.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	(void)argc;
	(void)argv;

	int arretEvent = 0, mouseX = 0, mouseY = 0, cycles = -1, cpt = 0;
	int debutTimer = 0;
	int score1 = 0, score2 = 0;
	enum EQUIPE e = EQUIPEDROITE;
	int etat = 1;

	//équipe gauche
	ordinateur_t *ordi1 = creerOrdi(EQUIPEGAUCHE);
	chargerQTable("nario.don", ordi1->QTable);
	ordinateur_t *ordi2 = creerOrdi(EQUIPEGAUCHE);
	chargerQTable("nario.don", ordi2->QTable);

	//équipe droite
	ordinateur_t *ordi3 = creerOrdi(EQUIPEDROITE);
	chargerQTable("valuigi.don", ordi3->QTable);
	ordinateur_t *ordi4 = creerOrdi(EQUIPEDROITE);
	chargerQTable("valuigi.don", ordi4->QTable);
	SDL_bool programON = SDL_TRUE;
	SDL_Event event;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_DisplayMode screen;

	/* Initialisation de la SDL  + gestion de l'échec possible */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		endSDL(0, "ERROR SDL INIT", window, renderer);

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

	/* Musique */
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *generique = Mix_LoadMUS("./resources/generique.mp3"); // Chargement de la musique
	Mix_Music *jeuMusique = Mix_LoadMUS("./resources/jeu.mp3");

	/* Création des textures */
	SDL_Texture *ballSprite = loadTextureFromImage("./resources/sprites/ball.png", window, renderer);
	SDL_Texture *playerSprite = loadTextureFromImage("./resources/sprites/playerViolet.png", window, renderer);
	SDL_Texture *playerRedSprite = loadTextureFromImage("./resources/sprites/player_red.png", window, renderer);
	SDL_Texture *terrainSpriteSheet = loadTextureFromImage("./resources/sprites/grass.png", window, renderer);
	SDL_Texture *mainTitle = loadTextureFromImage("./resources/TITLE.png", window, renderer);

	/* Boucle du jeu */
	Mix_PlayMusic(generique, 0); // Indice = priorité file
	// Mix_PauseMusic();
	// Mix_ResumeMusic();
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
						// movePlayer(player, HAUTD);
						arretEvent = 1;
						break;
					case SDLK_q:
						// movePlayer(player, GAUCHED);
						arretEvent = 1;
						break;
					case SDLK_s:
						// movePlayer(player, BASD);
						arretEvent = 1;
						break;
					case SDLK_d:
						// movePlayer(player, DROITD);
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
						int distance = sqrt(pow(mouseX - ball->x, 2) + pow(mouseY - ball->y, 2));
						int t = ball->x - mouseX;
						float a = acos((t * 1.0) / distance * 1.0);
						float angle = a * 180.0 / M_PI;
						pushBall(ball, angle, BALL_ACCELERATION);
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
			int random = rand() % 4;
			if (random == 0)
			{
				int action = choixAction(ordi1, perception(*ball, *(ordi1->player), *(ordi2->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action, ordi1, ball);
				playerBallCollision(ordi1->player, ball);

				int action4 = choixAction(ordi4, perception(*ball, *(ordi4->player), *(ordi2->player), *(ordi3->player), *(ordi1->player)), 0.5);
				faireAction(action4, ordi4, ball);
				playerBallCollision(ordi4->player, ball);

				int action2 = choixAction(ordi2, perception(*ball, *(ordi2->player), *(ordi1->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action2, ordi2, ball);
				playerBallCollision(ordi2->player, ball);

				int action3 = choixAction(ordi3, perception(*ball, *(ordi3->player), *(ordi1->player), *(ordi2->player), *(ordi4->player)), 0.5);
				faireAction(action3, ordi3, ball);
				playerBallCollision(ordi3->player, ball);
			}
			else if (random == 1)
			{
				int action3 = choixAction(ordi3, perception(*ball, *(ordi3->player), *(ordi1->player), *(ordi2->player), *(ordi4->player)), 0.5);
				faireAction(action3, ordi3, ball);
				playerBallCollision(ordi3->player, ball);

				int action = choixAction(ordi1, perception(*ball, *(ordi1->player), *(ordi2->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action, ordi1, ball);
				playerBallCollision(ordi1->player, ball);

				int action4 = choixAction(ordi4, perception(*ball, *(ordi4->player), *(ordi2->player), *(ordi3->player), *(ordi1->player)), 0.5);
				faireAction(action4, ordi4, ball);
				playerBallCollision(ordi4->player, ball);

				int action2 = choixAction(ordi2, perception(*ball, *(ordi2->player), *(ordi1->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action2, ordi2, ball);
				playerBallCollision(ordi2->player, ball);
			}
			else if (random == 2)
			{
				int action2 = choixAction(ordi2, perception(*ball, *(ordi2->player), *(ordi1->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action2, ordi2, ball);
				playerBallCollision(ordi2->player, ball);

				int action3 = choixAction(ordi3, perception(*ball, *(ordi3->player), *(ordi1->player), *(ordi2->player), *(ordi4->player)), 0.5);
				faireAction(action3, ordi3, ball);
				playerBallCollision(ordi3->player, ball);

				int action = choixAction(ordi1, perception(*ball, *(ordi1->player), *(ordi2->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action, ordi1, ball);
				playerBallCollision(ordi1->player, ball);

				int action4 = choixAction(ordi4, perception(*ball, *(ordi4->player), *(ordi2->player), *(ordi3->player), *(ordi1->player)), 0.5);
				faireAction(action4, ordi4, ball);
				playerBallCollision(ordi4->player, ball);
			}
			else
			{

				int action4 = choixAction(ordi4, perception(*ball, *(ordi4->player), *(ordi2->player), *(ordi3->player), *(ordi1->player)), 0.5);
				faireAction(action4, ordi4, ball);
				playerBallCollision(ordi4->player, ball);

				int action2 = choixAction(ordi2, perception(*ball, *(ordi2->player), *(ordi1->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action2, ordi2, ball);
				playerBallCollision(ordi2->player, ball);

				int action3 = choixAction(ordi3, perception(*ball, *(ordi3->player), *(ordi1->player), *(ordi2->player), *(ordi4->player)), 0.5);
				faireAction(action3, ordi3, ball);
				playerBallCollision(ordi3->player, ball);

				int action = choixAction(ordi1, perception(*ball, *(ordi1->player), *(ordi2->player), *(ordi3->player), *(ordi4->player)), 0.5);
				faireAction(action, ordi1, ball);
				playerBallCollision(ordi1->player, ball);
			}

			if (moveBall(ball, &e))
			{
				if (e == EQUIPEGAUCHE)
					score1++;
				if (e == EQUIPEDROITE)
					score2++;

				ball->x = (WINDOWW / 2) + rand() % 100 - 50;
				ball->y = (WINDOWH / 2) + rand() % 100 - 50;
				ball->v = 0;
				// player->x = WINDOWW / 4;
				// player->y = WINDOWH / 2;
				resetEmplacement(ordi1);
				resetEmplacement(ordi2);
				resetEmplacement(ordi3);
				resetEmplacement(ordi4);
			}
			// playerBallCollision(player, ball);
			if ((int)(time(NULL) - debutTimer) >= TIMEGAME)
			{
				etat = 2;
				Mix_PauseMusic();
			}

			/* Draw frame */
			afficherTerrain(terrainSpriteSheet, renderer);
			afficherTexture(ballSprite, renderer, ball->size, ball->size, ball->x, ball->y);
			afficherTexture(playerSprite, renderer, ordi3->player->w, ordi3->player->h, ordi3->player->x, ordi3->player->y);
			afficherTexture(playerSprite, renderer, ordi4->player->w, ordi4->player->h, ordi4->player->x, ordi4->player->y);

			afficherTexture(playerRedSprite, renderer, ordi1->player->w, ordi1->player->h, ordi1->player->x, ordi1->player->y);
			afficherTexture(playerRedSprite, renderer, ordi2->player->w, ordi2->player->h, ordi2->player->x, ordi2->player->y);
			afficherScore(score1, score2, font, window, renderer);
			char t[10];
			int min = (TIMEGAME - (int)(time(NULL) - debutTimer)) / 60;
			int sec = (TIMEGAME - (int)(time(NULL) - debutTimer)) % 60;
			sprintf(t, "%d : %d", min, sec);
			creationTexte(t, WINDOWW / 2, 50, font, window, renderer);

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
						debutTimer = time(NULL);
						Mix_PlayMusic(jeuMusique, 1);
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
			cpt++;
			afficherTexture(mainTitle, renderer, 600, 300, WINDOWW / 2, (WINDOWH / 2) + cos(cpt * 0.05) * 20 - 10);
			if (cpt % 80 < 40)
			{
				creationTexte("Press space to start", WINDOWW / 2, 3.5 * (WINDOWH / 4), font, window, renderer);
			}
			break;
		case 2: // Etat: Fin
			ecranFin(window, font, renderer, event, &score1, &score2, player, ball, &debutTimer, &etat, &programON, jeuMusique);
			break;
		default:
			break;
		}
		SDL_Delay(20);
		SDL_RenderPresent(renderer); // affichage
	}
	TTF_CloseFont(font);
	endSDL(1, "Normal ending", window, renderer);
	SDL_DestroyTexture(ballSprite);
	SDL_DestroyTexture(playerSprite);
	SDL_DestroyTexture(playerRedSprite);
	SDL_DestroyTexture(terrainSpriteSheet);
	SDL_DestroyTexture(mainTitle);
	TTF_Quit();
	IMG_Quit();
	SDL_AudioQuit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

// // main renforcement
// int main(int argc, char **argv)
// {
// 	ordinateur_t *ordi1,*ordi2;
// 	ordi1=creerOrdi(EQUIPEGAUCHE);
// 	ordi2=creerOrdi(EQUIPEDROITE);
// 	initQTableOrdi(ordi1);
// 	initQTableOrdi(ordi2);
// 	//afficherQTable(ordi1);
// 	//afficherQTable(ordi2);
// 	renforcement(ordi1,ordi2);

// 	// float **tab;
// 	// tab = malloc(3 * sizeof(float *));
// 	// tab[0] = malloc(2 * sizeof(float));
// 	// tab[1] = malloc(2 * sizeof(float));
// 	// tab[2] = malloc(2 * sizeof(float));
// 	// tab[0][0] = 5;
// 	// tab[1][0] = 5;
// 	// tab[2][0] = 5;
// 	// tab[0][1] = 5;
// 	// tab[1][1] = 5;
// 	// tab[2][1] = 5;

// 	// afficherQTable(tab, 3, 2);
// 	libererOrdi(ordi1);
// 	libererOrdi(ordi2);
// 	printf("-----------------FIN--------------\n");
// 	return 0;
// }