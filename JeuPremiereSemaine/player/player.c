#include "player.h"

void destroyPlayer(player_t *player)
{
    free(player);
}

void movePlayerDown(player_t *player)
{
    player->y += SPEED;
    if(player->y > WINDOWH){
        player->y = WINDOWH;
    }
}
void movePlayerUp(player_t *player)
{
    player->y -= SPEED;
    if(player->y < 0){
        player->y = 0;
    }
}

