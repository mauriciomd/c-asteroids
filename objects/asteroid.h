#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../internal/direction.h"

#define N_ASTEROID_POINTS         360
#define N_ASTEROIDS_SIZE          3
#define N_ASTEROIDS_TYPE_PER_SIZE 3
#define ASTEROID_MIN_VELOCITY     0.5

#define ASTEROID_TYPE_LARGER      1
#define ASTEROID_TYPE_MEDIUM      2
#define ASTEROID_TYPE_SMALL       3

typedef struct Asteroid {
    vector_t position;
    direction_t direction;
    double velocity;

    int type;
    double width;
    double height;
    SDL_Rect img;
    SDL_Point points[N_ASTEROID_POINTS];
} asteroid_t;

asteroid_t* create_asteroid(int type, int width, int height);
void set_asteroid_start_position(asteroid_t* a, int w, int h);
void clip_asteroid(asteroid_t* a);
void render_asteroid(SDL_Renderer* ctx, SDL_Texture* texture, asteroid_t* asteroid, bool show_borders);
void calculate_asteroid_points(asteroid_t* a);
void move_asteroid(asteroid_t* a, double w, double h);