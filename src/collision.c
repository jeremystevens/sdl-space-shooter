#include "collision.h"


int check_collision(
    const SDL_Rect *a,
    const SDL_Rect *b
)
{
    return (
        a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y
    );
}


int collisions_bullets_enemies(
    Bullet bullets[],
    Enemy enemies[]
)
{
    int points_earned = 0;

    for (int b = 0; b < MAX_BULLETS; b++)
    {
        if (!bullets[b].active)
        {
            continue;
        }

        SDL_Rect bullet_rect =
        {
            (int)bullets[b].x,
            (int)bullets[b].y,
            3,
            1
        };

        for (int e = 0; e < MAX_ENEMIES; e++)
        {
            if (!enemies[e].active)
            {
                continue;
            }

            SDL_Rect enemy_rect =
            {
                (int)enemies[e].x,
                (int)enemies[e].y,
                enemies[e].width,
                enemies[e].height
            };

            if (check_collision(&bullet_rect, &enemy_rect))
            {
                // Bullet is consumed by the collision.
                bullets[b].active = 0;

                // Damage the enemy.
                enemies[e].health--;

                if (enemies[e].health <= 0)
                {
                    enemies[e].active = 0;
                    points_earned += 10;
                }

                // This bullet cannot hit another enemy.
                break;
            }
        }
    }

    return points_earned;
}
