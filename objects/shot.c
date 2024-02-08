#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shot.h"

#define PI 3.14159

shot_t* create_shot(spaceship_t* s) {
    shot_t* shot = (shot_t*) malloc(sizeof(shot_t));
    
    shot->width = SHOT_WIDTH;
    shot->height = SHOT_HEIGHT;
    clip_shot(shot);    
    set_shot_start_position(shot, s);

    return shot;
}

void set_shot_start_position(shot_t* shot, spaceship_t* spaceship) {
    shot->direction.angle = spaceship->direction.angle;
    shot->direction.vector.x = spaceship->direction.vector.x;
    shot->direction.vector.y = spaceship->direction.vector.y;

    double theta = spaceship->direction.angle * PI / 180;
    shot->position.x = spaceship->position.x + spaceship->width/2 - shot->width/2 + cos(theta) * spaceship->width/2; 
    shot->position.y = spaceship->position.y + spaceship->height/2 - shot->height/2 + sin(theta) * spaceship->height/2;  
}

void clip_shot(shot_t* s) {
    s->img.x = 229;
    s->img.y = 149;
    s->img.w = s->width;
    s->img.h = s->height;
}

void render_shot(SDL_Renderer* ctx, SDL_Texture* texture, shot_t* shot, bool show_borders) {
    SDL_Rect render = { shot->position.x, shot->position.y, shot->width, shot->height };
    SDL_RenderCopy(ctx, texture, &shot->img, &render);
    if (show_borders) SDL_RenderDrawRect(ctx, &render);
}

void move_shot(shot_t* s) {
    s->position.x += SHOT_VELOCITY * s->direction.vector.x;
    s->position.y += SHOT_VELOCITY * s->direction.vector.y;
}