#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include <SDL.h>

#define MAX_ENEMY_BULLETS 30

typedef struct
{
    float x;
    float y;

    float dx;
    float dy;

    int active;

} EnemyBullet;


// Initialize the enemy bullet pool.
void enemy_bullets_init(EnemyBullet bullets[]);

// Fire an enemy bullet from an enemy position.
int enemy_bullets_fire(
    EnemyBullet bullets[],
    float x,
    float y
);

// Update all active enemy bullets.
void enemy_bullets_update(EnemyBullet bullets[]);


// Render all active enemy bullets.
void enemy_bullets_render(
    SDL_Renderer *renderer,
    const EnemyBullet bullets[]
);

#endif
