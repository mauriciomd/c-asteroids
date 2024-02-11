#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "asteroid.h"
#include "../internal/direction.h"

#define LEFT_BORDER  0
#define UPPER_BORDER 1
#define RIGHT_BORDER 2
#define DOWN_BORDER  3
#define THRESHOLD    50

#define GET_RADIUS(width) (width / 3.75)

asteroid_t* create_asteroid(int type, int width, int height, int id) {
    asteroid_t* asteroid = (asteroid_t*) malloc(sizeof(asteroid_t));
    asteroid->type = type;
    asteroid->id = id;

    clip_asteroid(asteroid);
    set_asteroid_start_position(asteroid, width, height);
    calculate_asteroid_points(asteroid);

    return asteroid;
}

void set_asteroid_start_position(asteroid_t* a, int w, int h) {    
    int border = rand() % 3;
    vector_t position;

    double angle = 0;
    if (border == LEFT_BORDER) {
        position.x = 0 - a->width - (rand() % THRESHOLD);
        position.y = rand() % (h / 2);
        angle = rand() % 90 + 20;
    } else if (border == UPPER_BORDER) {
        position.x = rand() % (w / 2);
        position.y = 0 - a->height - (rand() % THRESHOLD);
        angle = rand() % 180;
    } else if (border == RIGHT_BORDER) {
        position.x = w + a->width + (rand() % THRESHOLD);
        position.y = rand() % (h / 2);
        angle = rand() % 90 + 180;
    }

    a->velocity = (rand() % 10 + 1) / 10.0;
    if (a->velocity < ASTEROID_MIN_VELOCITY) {
        a->velocity = ASTEROID_MIN_VELOCITY;
    }

    a->position  = position;
    set_direction_vetor(&a->direction, angle);
}

void clip_asteroid(asteroid_t* a) {
    int asset = rand() % N_ASTEROIDS_TYPE_PER_SIZE;
    int type = a->type;

    double x, y, w, h, space;
    if (type == ASTEROID_TYPE_LARGER) {
        y = 8;
        x = 10;
        w = 68;
        h = 68;
        space = 80;
    } else if (type == ASTEROID_TYPE_MEDIUM) {
        y = 86;
        x = 8;
        w = 40;
        h = 40;
        space = 48;
    } else {
        y = 128;
        x = 0;
        w = 32;
        h = 32;
        space = 32;
    }

    a->width = w;
    a->height = h;
    a->img.x = x + space*asset;
    a->img.y = y;
    a->img.w = w;
    a->img.h = h;
}

void render_asteroid(SDL_Renderer* ctx, SDL_Texture* texture, asteroid_t* asteroid, bool show_borders) {
    SDL_Rect rect = { asteroid->position.x, asteroid->position.y, asteroid->width, asteroid->height };
    SDL_RenderCopy(ctx, texture, &asteroid->img, &rect);

    if (show_borders) SDL_RenderDrawPoints(ctx, asteroid->points, N_ASTEROID_POINTS);
}

void calculate_asteroid_points(asteroid_t* a) {
    double r = GET_RADIUS(a->width);
    double angle = 0;

    for (int i = 0; i < N_ASTEROID_POINTS; i++) {
        double theta = angle * 3.14159/180 ;
        angle = i * 360/N_ASTEROID_POINTS;

        a->points[i].x = (r * cos(theta) - r * sin(theta)) + a->position.x + a->width/2;
        a->points[i].y = (r * sin(theta) + r * cos(theta)) + a->position.y + a->height/2;
    }
}

void move_asteroid(asteroid_t* a, double w, double h) {
    double x = a->position.x + a->velocity * a->direction.vector.x;
    double y = a->position.y + a->velocity * a->direction.vector.y;

    if (x - a->width > w) { 
        x = -THRESHOLD;
    } else if (x + a->width < 0) {
        x = w + THRESHOLD; 
    } 

    if (y - a->height > h) { 
        y = -THRESHOLD; 
    } else if (y + a->height < 0) { 
        y = h + THRESHOLD;  
    }

    a->position.x = x;
    a->position.y = y;

    calculate_asteroid_points(a);
}

bool check_asteroid_collision(asteroid_t* a, double x, double y, double rs) {
    double r = GET_RADIUS(a->width);
    double dx = (a->position.x + a->width/2) - x;
    double dy = (a->position.y + a->height/2) - y;
    
    double distance = sqrt(pow(dx, 2) + pow(dy, 2));

    return distance <= r+rs;
}