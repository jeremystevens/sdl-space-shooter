#include "enemy_bullet.h"

// init enemy bullets
void enemy_bullets_init(EnemyBullet bullets[])
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        bullets[i].active = 0;
    }
}

// fire enemy bullets
int enemy_bullets_fire(
    EnemyBullet bullets[],
    float x,
    float y
)
{
    // Find an unused bullet slot.
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = x;
            bullets[i].y = y;

            // Enemy bullets travel toward the left.
            bullets[i].dx = -2.0f;
            bullets[i].dy = 0.0f;

            bullets[i].active = 1;

            return 1;
        }
    }

    // No free bullet slot was available.
    return 0;
}

// update enemy bullets
void enemy_bullets_update(EnemyBullet bullets[])
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            // Move the bullet.
            bullets[i].x += bullets[i].dx;
            bullets[i].y += bullets[i].dy;

            // Remove bullets that have left the screen.
            if (bullets[i].x < 0)
            {
                bullets[i].active = 0;
            }
        }
    }
}

// render enemy bullets
void enemy_bullets_render(
    SDL_Renderer *renderer,
    const EnemyBullet bullets[]
)
{
    // Bright red-orange enemy projectiles.
    SDL_SetRenderDrawColor(renderer, 255, 80, 40, 255);

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            SDL_Rect bullet_rect =
            {
                (int)bullets[i].x,
                (int)bullets[i].y,
                2,
                1
            };

            SDL_RenderFillRect(renderer, &bullet_rect);
        }
    }
}
