#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>

// Draw a single character using our built-in bitmap font.
void text_draw_char(
    SDL_Renderer *renderer,
    char character,
    int x,
    int y,
    int scale
);

// Draw a complete string using our built-in bitmap font.
void text_draw(
    SDL_Renderer *renderer,
    const char *text,
    int x,
    int y,
    int scale
);
#endif
