#include "enemy.h"

#include "game_config.h"

#include <stdlib.h>



void enemies_init(Enemy enemies[])
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = 0;
    }
}


void enemies_spawn(
    Enemy enemies[],
    Uint32 current_time,
    Uint32 *last_enemy_spawn
)
{
    // Don't spawn until enough time has passed.
    if (current_time - *last_enemy_spawn < ENEMY_SPAWN_TIME)
    {
        return;
    }

    // Find an unused enemy slot.
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].active)
        {
            enemies[i].x = 159.0f;
            // this keeps enemies from spawning in the HUD area
            enemies[i].y =
                (float)(HUD_HEIGHT + (rand() % (SCREEN_HEIGHT - HUD_HEIGHT - enemies[i].height)));

            enemies[i].dx = -1.0f;
            enemies[i].dy = 0.0f;

            // Current Scout dimensions.
            enemies[i].width = 12;
            enemies[i].height = 8;

            enemies[i].health = 1;
            enemies[i].active = 1;

            *last_enemy_spawn = current_time;

            break;
        }
    }
}


void enemies_update(Enemy enemies[])
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
        {
            enemies[i].x += enemies[i].dx;
            enemies[i].y += enemies[i].dy;

            // Recycle enemies once completely off-screen.
            if (enemies[i].x + enemies[i].width < 0)
            {
                enemies[i].active = 0;
            }
        }
    }
}


void enemies_render(
    SDL_Renderer *renderer,
    const Enemy enemies[]
)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].active)
        {
            continue;
        }

        int x = (int)enemies[i].x;
        int y = (int)enemies[i].y;


        // Red Scout body.
        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);

        SDL_RenderDrawLine(renderer, x + 2,  y,     x + 7,  y);
        SDL_RenderDrawLine(renderer, x + 1,  y + 1, x + 9,  y + 1);
        SDL_RenderDrawLine(renderer, x,      y + 2, x + 11, y + 2);

        SDL_RenderDrawLine(renderer, x + 2,  y + 3, x + 10, y + 3);
        SDL_RenderDrawLine(renderer, x + 2,  y + 4, x + 10, y + 4);

        SDL_RenderDrawLine(renderer, x,      y + 5, x + 11, y + 5);
        SDL_RenderDrawLine(renderer, x + 1,  y + 6, x + 9,  y + 6);
        SDL_RenderDrawLine(renderer, x + 2,  y + 7, x + 7,  y + 7);


        // Yellow/orange center detail.
        SDL_SetRenderDrawColor(renderer, 255, 200, 50, 255);

        SDL_Rect center =
        {
            x + 2,
            y + 3,
            3,
            2
        };

        SDL_RenderFillRect(renderer, &center);
    }
}
