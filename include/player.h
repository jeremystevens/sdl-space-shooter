#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

// player's ship and its current state.
typedef struct
{
    float x;
    float y;
    int width;
    int height;
    float speed;
    int lives;
} Player;

void player_init(Player *player);
void player_update(Player *player, const Uint8 *keyboard);
void player_render(SDL_Renderer *renderer, const Player *player);
#endif
