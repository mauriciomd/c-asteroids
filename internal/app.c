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

    SDL_Event event;
    while (true) {
        int r = SDL_PollEvent(&event);
        if (r > 0) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_Q) {
                break;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                rotate_anticlockwise(app->player);
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                rotate_clockwise(app->player);
            }
        }
        
        SDL_RenderClear(app->renderer);
        
        SDL_FillRect(app->surface, NULL, SDL_MapRGB(app->surface->format, 0x00, 0x0, 0x0));
        render_spaceship(app->renderer, app->player);
        
        SDL_RenderPresent(app->renderer);
    }
    
    destroy_game_objects(app);
}

void destroy_game_objects(app_t* app) {
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
    
    if (app->player != NULL) free(app->player);
    if (app != NULL) free(app);
    
    SDL_Quit();
}