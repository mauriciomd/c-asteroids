#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "app.h"

app_t* init_app(int width, int height) {
    app_t* app = (app_t*) malloc(sizeof(app_t));
    app->shots = create_list();
    app->asteroids = create_list();

    app->screen_width = width;
    app->screen_height = height;

    init_sdl(app);
    load_texture(app, "./assets/asteroids.png");
    create_player(app);
    init_asteroids(app);
    
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

    app->window = SDL_CreateWindow(
        "C Invaders", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        app->screen_width, 
        app->screen_height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (app->window == NULL) {
        printf("SDL Window could not be created. Error: %s", SDL_GetError());
        exit(1);
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->window == NULL) {
        printf("SDL Renderer could not be created. Error: %s", SDL_GetError());
        exit(1);
    }
}

void load_texture(app_t* app, const char* path) {
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s. SDL_image Error: %s\n", path, IMG_GetError());
        exit(1);
    }

    app->texture = SDL_CreateTextureFromSurface(app->renderer, loadedSurface);
    if (app->texture == NULL) {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(loadedSurface);
}

void create_player(app_t* app) {
    app->player = init_spaceship(app->screen_width, app->screen_height); 
}

void init_asteroids(app_t* app) {
    for (int i = 0; i < N_INITIAL_ASTEROIDS; i++) {
        asteroid_t* asteroid = create_asteroid(ASTEROID_TYPE_LARGER, app->screen_width, app->screen_height, i);
        list_insert(app->asteroids, (void*) asteroid);
    }
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
                break;
            case SDL_SCANCODE_RIGHT:
                app->keys.is_right_pressed = true;    
                break;
            case SDL_SCANCODE_UP:
                app->keys.is_up_pressed = true;    
                break;
        default:
            break;;
        }
    }

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.scancode)
        {
            case SDL_SCANCODE_Q:
                app->is_running = false;
                break;
            case SDL_SCANCODE_LEFT:
                app->keys.is_left_pressed = false;    
                break;
            case SDL_SCANCODE_RIGHT:
                app->keys.is_right_pressed = false;    
                break;
            case SDL_SCANCODE_UP:
                app->keys.is_up_pressed = false;    
                break;
            case SDL_SCANCODE_SPACE:
                list_insert(app->shots, (void*) create_shot(app->player));
                break;
            case SDL_SCANCODE_D:
                app->show_borders = !app->show_borders;
                break;
            case SDL_SCANCODE_F:
                app->is_movement_frozen = !app->is_movement_frozen;
                break;
        default:
            break;
        }
    }
}

void process_scene(app_t* app) {
    if (app->keys.is_up_pressed) move_spaceship(app->player);
    if (app->keys.is_left_pressed) rotate_anticlockwise(app->player);
    if (app->keys.is_right_pressed) rotate_clockwise(app->player);

    if (is_empty_list(app->asteroids)) {
        app->is_running = false;
        return;
    }

    list_foreach_element(app->shots, (void*) app, &process_get_shot);
    list_foreach_element(app->asteroids, (void*) app, &process_get_asteroid);
    list_foreach_element(app->shots, (void*) app, &check_shot_collision);
}

void check_shot_collision(void* a, void* s) {
    app_t* app = (app_t*) a;
    shot_t* shot = (shot_t*) s;

    // Not ideal implementation
    if (is_empty_list(app->asteroids)) return;

    node_t* element = app->asteroids->head;
    while (element != NULL) {
        asteroid_t* ast = (asteroid_t*) element->data;
        element = element->next;
        bool is_collided = check_asteroid_collision(
            ast, 
            shot->position.x + shot->width/2,
            shot->position.y + shot->height/2, 
            shot->width/2);
        
        if (is_collided) {
            list_remove(app->shots, (void*) shot);
            if (ast->type != ASTEROID_TYPE_SMALL) {
                list_insert(app->asteroids, (void*) create_child_asteroid(ast, true));
                list_insert(app->asteroids, (void*) create_child_asteroid(ast, false));
            } 
            list_remove(app->asteroids, (void*) ast);
            return;
        }
    }
}

void process_get_shot(void* a, void* s) {
    app_t* app = (app_t*) a;
    shot_t* shot = (shot_t*) s;
    
    if (app->is_movement_frozen) return;
    move_shot(shot);

    bool is_px_out = shot->position.x < 0 || shot->position.x > app->screen_width;
    bool is_py_out = shot->position.y < 0 || shot->position.y > app->screen_height; 
    if (is_px_out || is_py_out) {
        list_remove(app->shots, s);
    }
}

void process_get_asteroid(void* a, void* ast) {
    app_t* app = (app_t*) a;
    asteroid_t* asteroid = (asteroid_t*) ast;
    
    if (app->is_movement_frozen) return;
    move_asteroid(asteroid, app->screen_width, app->screen_height);
}

void render_objects(app_t* app) {
    SDL_RenderClear(app->renderer);
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    
    render_spaceship(app->renderer, app->texture,app->player, app->show_borders);    
    list_foreach_element(app->shots, (void*) app, &render_get_shot);
    list_foreach_element(app->asteroids, (void*) app, &render_get_asteroid);
    SDL_RenderPresent(app->renderer);
}

void render_get_shot(void* a, void* s) {
    app_t* app = (app_t*) a;
    shot_t* shot = (shot_t*) s;
    render_shot(app->renderer, app->texture, shot, app->show_borders);
}

void render_get_asteroid(void* a, void* ast) {
    app_t* app = (app_t*) a;
    asteroid_t* asteroid = (asteroid_t*) ast;

    render_asteroid(app->renderer, app->texture, asteroid, app->show_borders);
}

void destroy_game_objects(app_t* app) {
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
    
    free_list(app->shots);
    free_list(app->asteroids);
    free(app->player);
    free(app);
    
    SDL_Quit();
}