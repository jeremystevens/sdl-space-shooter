#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "enemy_bullet.h"

#define MAX_ENEMIES 20
#define ENEMY_SPAWN_TIME 1000

typedef struct
{
    float x;
    float y;

    float dx;
    float dy;

    int width;
    int height;

    int health;
    int active;

    Uint32 last_shot_time;
    Uint32 fire_delay;

} Enemy;

// Initialize the enemy pool.
void enemies_init(Enemy enemies[]);


// Spawn an enemy when the spawn timer expires.
void enemies_spawn(
    Enemy enemies[],
    Uint32 current_time,
    Uint32 *last_enemy_spawn
);


int enemies_fire(
    Enemy enemies[],
    EnemyBullet bullets[],
    Uint32 current_time
);

// Update all active enemies.
void enemies_update(Enemy enemies[]);


// Render all active enemies.
void enemies_render(
    SDL_Renderer *renderer,
    const Enemy enemies[]
);

#endif
