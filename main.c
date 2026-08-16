#include <stdio.h>  // Provides printf() for console output and error messages
#include <SDL.h>    // SDL2 functions, types, and constants
#include <stdlib.h>

//include  custom headers
#include "player.h"
#include "starfield.h"
#include "bullet.h"
#include "audio.h"
#include "enemy.h"
#include "collision.h"

// Set the Frames per Second
#define TARGET_FPS 60
#define FRAME_TIME (1000 / TARGET_FPS)


// define score & set score to zero
int score = 0;

int main(void)
{
    // Create an array capable of storing all background stars.
    Star stars[MAX_STARS];
    starfield_init(stars);

    // SDL_Init() returns 0 on success and a non-zero value on failure.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // init Laser audio
    LaserSound laser;

    if (!audio_init(&laser))
    {
        printf("Audio initialization failed.\n");
    }

    //  audio_play_laser(&laser);

    // Create the main game window.
    // SDL_CreateWindow() returns a pointer to the new window,
    // or NULL if the window could not be created.
    SDL_Window *window = SDL_CreateWindow(
                             "Space Shooter",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             640,
                             480,
                             SDL_WINDOW_SHOWN
                         );

    // Always check pointers returned by SDL before using them.
    if (window == NULL)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create the renderer used to draw graphics into our window.
    // -1 tells SDL to choose an appropriate graphics driver.
    // SDL_RENDERER_ACCELERATED requests hardware-accelerated rendering.
    SDL_Renderer *renderer = SDL_CreateRenderer(
                                 window,
                                 -1,
                                 SDL_RENDERER_ACCELERATED
                             );

    if (renderer == NULL)
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());

        // The window was already created, destroy it before exiting.
        SDL_DestroyWindow(window);
        audio_shutdown();
        SDL_Quit();
        return 1;
    }

    // Use the same 160x120 logical resolution as the original game.

    //  scale this to our 640x480 window.
    if (SDL_RenderSetLogicalSize(renderer, 160, 120) != 0)
    {
        printf("Failed to set logical resolution: %s\n", SDL_GetError());

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create and initialize the player.
    Player player;
    player_init(&player);

    // Create the player's bullet pool.
    Bullet bullets[MAX_BULLETS];
    // init bullets
    bullets_init(bullets);

    // Main game-loop control.As long as running the game continues.
    int running = 1;

    // SDL_Event stores information about events such as
    // keyboard input, mouse input, and closing the window.
    SDL_Event event;

    // Stores the time when the previous bullet was fired.
    Uint32 last_shot_time = 0;

    // Create the enemy pool.
    Enemy enemies[MAX_ENEMIES];

    // init enemies
    enemies_init(enemies);

    // spawn timer for enemies
    Uint32 last_enemy_spawn = 0;
    // -------------------------
    // Main Game Loop
    // -------------------------
    while (running)
    {
        Uint32 frame_start = SDL_GetTicks();
        // Process all events currently waiting in SDL's event queue.
        // &event passes the address of our event variable so that
        // SDL_PollEvent() can write event information into it.
        while (SDL_PollEvent(&event))
        {
            // SDL_QUIT occurs when the user requests that the
            // application close, such as clicking the window's X button.
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }

        } // end of SDL pollEvent

        // Get the current state of the keyboard.
        // This lets us detect keys that are being held down.
        const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

        // player movement
        player_update(&player, keyboard);

        // Fire continuously while the Space bar is held down.
        if (keyboard[SDL_SCANCODE_SPACE])
        {
            Uint32 current_time = SDL_GetTicks();

            if (bullets_fire(
                        bullets,
                        &player,
                        current_time,
                        &last_shot_time))
            {
                audio_play_laser(&laser);
            }
        }

        // update bullets
        bullets_update(bullets);

        // bullets against enemies
        score += collisions_bullets_enemies(
                     bullets,
                     enemies
                 );

        // Spawn a new enemy after enough time has passed.
        Uint32 current_time = SDL_GetTicks();

        // enemy spawning
        enemies_spawn(
            enemies,
            current_time,
            &last_enemy_spawn
        );

        // Update all active enemies.
        enemies_update(enemies);

        // update the scrolling starfield
        starfield_update(stars);

        // Set the drawing color to opaque black.
        // The four values represent Red, Green, Blue, and Alpha.
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Clear the previous frame using the current drawing color.
        SDL_RenderClear(renderer);

        // Render star field
        starfield_render(renderer, stars);

        // Render bullets
        bullets_render(renderer, bullets);

        // Draw active enemies
        enemies_render(renderer, enemies);
        // Draw the player.
        player_render(renderer, &player);

        // Display the completed frame in the window.
        SDL_RenderPresent(renderer);
        // Calculate how long this frame took to process.
        Uint32 frame_time = SDL_GetTicks() - frame_start;

        // If the frame finished early, wait for the remaining time.
        if (frame_time < FRAME_TIME)
        {
            SDL_Delay(FRAME_TIME - frame_time);
        }

    } // end of game loop

    // -------------------------
    // Cleanup
    // -------------------------

    // Destroy resources in reverse order of their creation.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Shut down all initialized SDL systems.
    SDL_Quit();

    // Returning 0 tells the operating system that the program
    // finished successfully.
    return 0;

} // end of main
