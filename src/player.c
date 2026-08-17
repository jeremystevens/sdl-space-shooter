#include "player.h"
#include <stdio.h>
// set the invulnerable  time between deaths
#define INVULNERABILITY_TIME 1500

void player_init(Player *player)
{
    player->x = 20.0f;
    player->y = 60.0f;
    player->width = 16;
    player->height = 10;
    player->speed = 2.0f;
    player->lives = 3;
    player->invulnerable = 0;
    player->invulnerable_until = 0;
}
// Update player movement when keys are pressed
void player_update(
    Player *player,
    const Uint8 *keyboard,
    Uint32 current_time
)
{

    // Move the player while the arrow keys are held down.
    if (keyboard[SDL_SCANCODE_UP])
    {
        player->y -= player->speed;
    }

    if (keyboard[SDL_SCANCODE_DOWN])
    {
        player->y += player->speed;
    }

    if (keyboard[SDL_SCANCODE_LEFT])
    {
        player->x -= player->speed;
    }

    if (keyboard[SDL_SCANCODE_RIGHT])
    {
        player->x += player->speed;
    }

    // Keep the player inside the 160x120 game area.
    if (player->x < 0)
    {
        player->x = 0;
    }

    if (player->y < 0)
    {
        player->y = 0;
    }

    if (player->x + player->width > 160)
    {
        player->x = 160 - player->width;
    }

    if (player->y + player->height > 120)
    {
        player->y = 120 - player->height;
    }
    // End invulnerability after the timer expires.
    if (player->invulnerable &&
            current_time >= player->invulnerable_until)
    {
        player->invulnerable = 0;
    }
}

// player damage function
void player_take_damage(Player *player, Uint32 current_time)
{
    // Ignore damage while the player is invulnerable.
    if (player->invulnerable || player->lives <= 0)
    {
        return;
    }

    // Remove one life.
    player->lives--;

    if (player->lives < 0)
    {
        player->lives = 0;
    }

    printf("Player hit! Lives remaining: %d\n", player->lives);

    // Temporarily protect the player from additional damage.
    player->invulnerable = 1;
    player->invulnerable_until =
        current_time + INVULNERABILITY_TIME;
}

// Render the players ship
void player_render(SDL_Renderer *renderer, const Player *player)
{
    // Blink the ship while temporarily invulnerable.
    if (player->invulnerable)
    {
        Uint32 current_time = SDL_GetTicks();

        // Alternate visibility every 100 milliseconds.
        if ((current_time / 100) % 2 == 0)
        {
            return;
        }
    }

    int x = (int)player->x;
    int y = (int)player->y;

    // Draw the gray body of the player's ship.
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    SDL_RenderDrawLine(renderer, x + 5, y,     x + 8,  y);
    SDL_RenderDrawLine(renderer, x + 4, y + 1, x + 10, y + 1);
    SDL_RenderDrawLine(renderer, x + 2, y + 2, x + 12, y + 2);
    SDL_RenderDrawLine(renderer, x + 1, y + 3, x + 14, y + 3);

    SDL_RenderDrawLine(renderer, x,     y + 4, x + 15, y + 4);
    SDL_RenderDrawLine(renderer, x,     y + 5, x + 15, y + 5);

    SDL_RenderDrawLine(renderer, x + 1, y + 6, x + 14, y + 6);
    SDL_RenderDrawLine(renderer, x + 2, y + 7, x + 12, y + 7);
    SDL_RenderDrawLine(renderer, x + 4, y + 8, x + 10, y + 8);
    SDL_RenderDrawLine(renderer, x + 5, y + 9, x + 8,  y + 9);

    // Draw the orange engine flame.
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

    SDL_RenderDrawLine(renderer, x - 3, y + 4, x - 1, y + 4);
    SDL_RenderDrawLine(renderer, x - 3, y + 5, x - 1, y + 5);

    // Draw the light-blue cockpit.
    SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);

    SDL_Rect cockpit =
    {
        x + 9,
        y + 3,
        3,
        4
    };

    SDL_RenderFillRect(renderer, &cockpit);
}
