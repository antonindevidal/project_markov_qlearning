#ifndef __FONCTIONS_SDL_H__
#define __FONCTIONS_SDL_H__
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* DECLARATION DES PROTOTYPES */

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void afficher_texture_full(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer);
void afficher_texture(SDL_Texture *ma_texture, SDL_Window *window, SDL_Renderer *renderer);

#endif
