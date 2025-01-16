#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

void update_texture(SDL_Texture *tex, const uint8_t *data, int n_data);

int init_sdl();

void draw(SDL_Renderer *renderer, SDL_Texture *texture);

#endif
