#ifndef TERRAIN_H
#define TERRAIN_H

#include "../fonctionsSDL.h"
#include "../const.h"

#define TERRAINSPRITESIZE 32
#define LINETHICKNESS 4

void afficherTerrain(SDL_Texture *texture,SDL_Renderer * renderer);
void afficherTileTerrain(int i, int j,SDL_Texture * texture,SDL_Renderer *renderer);

#endif