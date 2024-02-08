#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "../internal/direction.h"
#include "spaceship.h"

#define SHOT_WIDTH    8 
#define SHOT_HEIGHT   8
#define SHOT_VELOCITY 2

typedef struct Shot
{   
    vector_t position;
    direction_t direction;

    double height;
    double width;
    SDL_Rect img;
} shot_t;

shot_t* create_shot(spaceship_t* s);
void set_shot_start_position(shot_t* shot, spaceship_t* spaceship);
void clip_shot(shot_t* s);
void render_shot(SDL_Renderer* ctx, SDL_Texture* texture, shot_t* shot, bool show_borders);
void move_shot(shot_t* s);