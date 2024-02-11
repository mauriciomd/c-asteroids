#ifndef SPACESHIP
#define SPACESHIP

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../internal/direction.h"

#define SPACESHIP_WIDTH          30
#define SPACESHIP_HEIGHT         22
#define SPACESHIP_VELOCITY       1
#define SPACESHIP_ROTATION_ANGLE 0.7

typedef struct SpaceShip {
    vector_t position;
    direction_t direction;
    double force;
    double height;
    double width;
    SDL_Rect img;
    SDL_Point borders[4];
    int n_points;

} spaceship_t;

spaceship_t* init_spaceship(double s_width, double s_height);
void set_initial_location_direction(spaceship_t* s, double w, double h);
void clip_spaceship(spaceship_t* s);
void render_spaceship(SDL_Renderer* ctx, SDL_Texture* texture, spaceship_t* s, bool show_borders);
void rotate_clockwise(spaceship_t* s);
void rotate_anticlockwise(spaceship_t* s);
void calculate_points(spaceship_t* s);
void move_spaceship(spaceship_t* s);

#endif