#include "bullet.h"

// Initialize the bullet pool.
// All bullets begin inactive and are available for use.
void bullets_init(Bullet bullets[])
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = 0;
    }
}


// Fire a bullet if the weapon cooldown has expired.
int bullets_fire(
    Bullet bullets[],
    const Player *player,
    Uint32 current_time,
    Uint32 *last_shot_time
)
{
    // Don't fire if the cooldown has not finished yet.
    if (current_time - *last_shot_time < FIRE_COOLDOWN)
    {
        return 0;
    }

    // Cooldown hasn't expired.
    if (current_time - *last_shot_time < FIRE_COOLDOWN)
    {
        return 0;
    }

    // Find an unused bullet.
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = player->x + player->width;
            bullets[i].y = player->y + (player->height / 2);

            bullets[i].dx = 4.0f;
            bullets[i].dy = 0.0f;
            bullets[i].active = 1;

            *last_shot_time = current_time;

            // Tell the caller that a bullet was actually fired.
            return 1;
        }
    }

    // Bullet pool was full.
    return 0;
}



// Update all active bullets.
void bullets_update(Bullet bullets[])
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].x += bullets[i].dx;
            bullets[i].y += bullets[i].dy;

            // Recycle bullets that leave the right side of the screen.
            if (bullets[i].x >= 160)
            {
                bullets[i].active = 0;
            }
        }
    }
}


// Render all active bullets.
void bullets_render(
    SDL_Renderer *renderer,
    const Bullet bullets[]
)
{
    // Yellow projectile color.
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            SDL_Rect bullet_rect =
            {
                (int)bullets[i].x,
                (int)bullets[i].y,
                3,
                1
            };

            SDL_RenderFillRect(renderer, &bullet_rect);
        }
    }
}
