#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "spaceship.h"

spaceship_t* init_spaceship(double s_width, double s_height) {
    spaceship_t* spaceship = (spaceship_t*) malloc(sizeof(spaceship_t));

    spaceship->n_points = 4;
    spaceship->width = SPACESHIP_WIDTH;
    spaceship->height = SPACESHIP_HEIGHT;
    
    set_initial_location_direction(spaceship, s_width, s_height);
    clip_spaceship(spaceship);
    calculate_points(spaceship);

    return spaceship;
}

void set_initial_location_direction(spaceship_t* s, double w, double h) {
    s->position.x = w/2 - s->width/2;
    s->position.y = h/2 - s->height/2;
    
    s->direction.vector.x = 1;
    s->direction.vector.y = 0;
    s->direction.angle = 0;
}

void clip_spaceship(spaceship_t* s) {
    s->img.x = 110;
    s->img.y = 132;
    s->img.w = s->width;
    s->img.h = s->height;
}

void render_spaceship(SDL_Renderer* ctx, SDL_Texture* texture, spaceship_t* s, bool show_borders) {
    SDL_RenderClear(ctx);
    SDL_Rect render = { s->position.x, s->position.y, s->width, s->height };
    SDL_RenderCopyEx(ctx, texture, &s->img, &render, s->direction.angle, NULL, SDL_FLIP_NONE);
    
    if (!show_borders) return;
    
    SDL_SetRenderDrawColor(ctx, 200, 200, 200, 1);
    for (int i = 1; i < s->n_points; i++) {
        SDL_RenderDrawLine(ctx, s->borders[i-1].x, s->borders[i-1].y, s->borders[i].x, s->borders[i].y);
    }
    SDL_RenderDrawLine(ctx, s->borders[0].x, s->borders[0].y, s->borders[s->n_points-1].x, s->borders[s->n_points-1].y);
}

void rotate_clockwise(spaceship_t* s) {
    direction_increase_angle(&s->direction, SPACESHIP_ROTATION_ANGLE);
    calculate_points(s);
}

void rotate_anticlockwise(spaceship_t* s) {
    direction_decrease_angle(&s->direction, SPACESHIP_ROTATION_ANGLE);
    calculate_points(s);
}

void calculate_points(spaceship_t* s) {
    double x1 = s->width/2;
    double x2 = 0 - s->width/2;
    double y1 = s->height/2;
    double y2 = 0 - s->height/2;

    double theta = s->direction.angle * 3.14 / 180;
    s->borders[0].x = x1 * cos(theta) - y1 * sin(theta);
    s->borders[0].y = x1 * sin(theta) + y1 * cos(theta);

    s->borders[1].x = x2 * cos(theta) - y1 * sin(theta);
    s->borders[1].y = x2 * sin(theta) + y1 * cos(theta);

    s->borders[2].x = x2 * cos(theta) - y2 * sin(theta);
    s->borders[2].y = x2 * sin(theta) + y2 * cos(theta);

    s->borders[3].x = x1 * cos(theta) - y2 * sin(theta);
    s->borders[3].y = x1 * sin(theta) + y2 * cos(theta);

    for (int i = 0; i < s->n_points; i++) {
         s->borders[i].x += s->position.x + s->width/2;
         s->borders[i].y += s->position.y + s->height/2;
    }
}

void move_spaceship(spaceship_t* s) {
    s->position.x += SPACESHIP_VELOCITY * s->direction.vector.x;
    s->position.y += SPACESHIP_VELOCITY * s->direction.vector.y;
    calculate_points(s);
}