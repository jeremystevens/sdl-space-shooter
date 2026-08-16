#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

#include "bullet.h"
#include "enemy.h"


// Returns 1 if two rectangles overlap, otherwise 0.
int check_collision(
    const SDL_Rect *a,
    const SDL_Rect *b
);


// Handle collisions between player bullets and enemies.
// Returns the number of score points earned.
int collisions_bullets_enemies(
    Bullet bullets[],
    Enemy enemies[]
);


#endif
