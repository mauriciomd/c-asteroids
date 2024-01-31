#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "spaceship.h"

spaceship_t* init_spaceship(SDL_Renderer* ctx, const char* texturePath, double s_width, double s_height) {
    spaceship_t* spaceship = (spaceship_t*) malloc(sizeof(spaceship_t));

    spaceship->height = 32;
    spaceship->width = 48;
    
    set_initial_location_direction(spaceship, s_width, s_height);
    load_texture(ctx, spaceship, texturePath);

    return spaceship;
}

void set_initial_location_direction(spaceship_t* s, double w, double h) {
    s->position.x = w/2 - s->width/2;
    s->position.y = h/2 - s->height/2;
    
    s->direction.vector.x = 1;
    s->direction.vector.y = 0;
    s->direction.angle = 0;
}

void load_texture(SDL_Renderer* ctx, spaceship_t* s, const char* path) {
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s. SDL_image Error: %s\n", path, IMG_GetError());
        exit(1);
    }

    s->texture = SDL_CreateTextureFromSurface(ctx, loadedSurface);
    if (s->texture == NULL) {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    s->img.x = 96;
    s->img.y = 128;
    s->img.w = s->width;
    s->img.h = s->height;

    SDL_FreeSurface(loadedSurface);
}

void render_spaceship(SDL_Renderer* ctx, spaceship_t* s) {
    SDL_Rect renderQuad = { s->position.x, s->position.y, s->width, s->height };
    SDL_RenderCopyEx(ctx, s->texture, &s->img, &renderQuad, s->direction.angle, NULL, SDL_FLIP_NONE);
}

void rotate_clockwise(spaceship_t* s) {
    s->direction.angle += 1; // must be reviewed

    s->direction.vector.x = cos(s->direction.angle);
    s->direction.vector.y = sin(s->direction.angle);
}

void rotate_anticlockwise(spaceship_t* s) {
    s->direction.angle -= 1; // must be reviewed

    s->direction.vector.x = cos(s->direction.angle);
    s->direction.vector.y = sin(s->direction.angle);
}