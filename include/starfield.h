#ifndef STARFIELD_H
#define STARFIELD_H

#include <SDL.h>

#define MAX_STARS 30

// Represents one star in the scrolling background.
typedef struct
{
    float x;
    float y;
    float speed;
} Star;

void starfield_init(Star stars[]);
void starfield_update(Star stars[]);
void starfield_render(SDL_Renderer *renderer, const Star stars[]);

#endif
