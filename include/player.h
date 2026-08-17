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

    // Damage / invulnerability state.
    int invulnerable;
    Uint32 invulnerable_until;

} Player;
void player_init(Player *player);
void player_update(
    Player *player,
    const Uint8 *keyboard,
    Uint32 current_time
);
// player takes takes damage
void player_take_damage(Player *player, Uint32 current_time);
void player_render(SDL_Renderer *renderer, const Player *player);
#endif
