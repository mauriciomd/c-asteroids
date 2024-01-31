#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "app.h"

app_t* init_app(int width, int height) {
    app_t* app = (app_t*) malloc(sizeof(app_t));
    
    app->screen_width = width;
    app->screen_height = height;

    init_sdl(app);
    create_player(app);
    
    return app;
}

void init_sdl(app_t* app) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initializes. Error: %s", SDL_GetError());
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("Unable to initialize the IMG Subsystem.");
        exit(1);
    }

    app->window = SDL_CreateWindow("C Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->screen_width, app->screen_height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (app->window == NULL) {
        printf("SDL Window could not be created. Error: %s", SDL_GetError());
        exit(1);
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->window == NULL) {
        printf("SDL Renderer could not be created. Error: %s", SDL_GetError());
        exit(1);
    }

    app->surface = SDL_GetWindowSurface(app->window);
}

void create_player(app_t* app) {
    app->player = init_spaceship(app->renderer, "./assets/asteroids.png", app->screen_width, app->screen_height); 
}

void run_app(app_t* app) {
    app->is_running = true;
    SDL_Event event;

    while (app->is_running) {
        while (SDL_PollEvent(&event) > 0) {
            process_events(event, app);
        }

        process_scene(app);
        render_objects(app);    
    }
    
    destroy_game_objects(app);
}

void process_events(SDL_Event event, app_t* app) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode)
        {
            case SDL_SCANCODE_LEFT:
                app->keys.is_left_pressed = true;    
                return;
            case SDL_SCANCODE_RIGHT:
                app->keys.is_right_pressed = true;    
                return;
            case SDL_SCANCODE_UP:
                app->keys.is_up_pressed = true;    
                return;
        default:
            return;
        }
    }

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.scancode)
        {
            case SDL_SCANCODE_Q:
                app->is_running = false;
                return;
            case SDL_SCANCODE_LEFT:
                app->keys.is_left_pressed = false;    
                return;
            case SDL_SCANCODE_RIGHT:
                app->keys.is_right_pressed = false;    
                return;
            case SDL_SCANCODE_UP:
                app->keys.is_up_pressed = false;    
                return;
        default:
            break;
        }
    }
}

void process_scene(app_t* app) {
    if (app->keys.is_up_pressed) move_spaceship(app->player);
    if (app->keys.is_left_pressed) rotate_anticlockwise(app->player);
    if (app->keys.is_right_pressed) rotate_clockwise(app->player);
}

void render_objects(app_t* app) {
    SDL_RenderClear(app->renderer);
    render_spaceship(app->renderer, app->player);
    // SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 1);
    // SDL_RenderDrawLine(app->renderer, app->player->position.x, app->player->position.y, app->player->position.x + 20 * app->player->direction.vector.x, app->player->position.y + 20 * app->player->direction.vector.y);
    
    SDL_RenderPresent(app->renderer);
}

void destroy_game_objects(app_t* app) {
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
    
    if (app->player != NULL) free(app->player);
    if (app != NULL) free(app);
    
    SDL_Quit();
}