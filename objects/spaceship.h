#include <SDL2/SDL.h>

typedef struct Vector {
    double x;
    double y;
} vector_t;

typedef struct Direction {
    vector_t vector;
    double angle;
} direction_t;

typedef struct SpaceShip {
    vector_t position;
    direction_t direction;
    double force;
    double height;
    double width;

    SDL_Texture* texture;
    SDL_Rect img;
} spaceship_t;

spaceship_t* init_spaceship(SDL_Renderer* ctx, const char *texturePath, double s_width, double s_height);
void set_initial_location_direction(spaceship_t* s, double w, double h);
void render_spaceship(SDL_Renderer* ctx, spaceship_t* s);
void rotate_clockwise(spaceship_t* s);
void rotate_anticlockwise(spaceship_t* s);

void load_texture(SDL_Renderer* ctx, spaceship_t* s, const char* path); // Should be moved