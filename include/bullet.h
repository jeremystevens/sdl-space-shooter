#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include "player.h"

#define MAX_BULLETS 50
#define FIRE_COOLDOWN 150

typedef struct
{
    float x;
    float y;
    float dx;
    float dy;
    int active;
} Bullet;

void bullets_init(Bullet bullets[]);

int bullets_fire(
    Bullet bullets[],
    const Player *player,
    Uint32 current_time,
    Uint32 *last_shot_time
);

void bullets_update(Bullet bullets[]);

void bullets_render(
    SDL_Renderer *renderer,
    const Bullet bullets[]
);

#endif
