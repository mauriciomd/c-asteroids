#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "linkedlist.h"
#include "../objects/spaceship.h"
#include "../objects/shot.h"
#include "../objects/asteroid.h"

#define N_INITIAL_ASTEROIDS 8
#define MAX_ASTEROIDS       32

typedef struct KeyPressed {
    bool is_left_pressed;
    bool is_right_pressed;
    bool is_up_pressed;
} keypressed_t;

typedef struct App {
    bool is_running;
    bool show_borders;
    bool is_movement_frozen;

    int screen_width;
    int screen_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    keypressed_t keys;
    spaceship_t* player; 
    list_t* shots;
    list_t* asteroids;
} app_t;

app_t* init_app(int width, int height);
void init_sdl(app_t* app);
void load_texture(app_t* app, const char* path);
void run_app(app_t *app);
void create_player(app_t* app);
void init_asteroids(app_t* app);
void process_events(SDL_Event event, app_t* app);
void process_scene(app_t* app);
void process_get_shot(void* a, void* s);
void process_get_asteroid(void* a, void* ast);
void render_objects(app_t* app);
void render_get_shot(void* a, void* s);
void render_get_asteroid(void* a, void* ast);
void destroy_game_objects(app_t* app);
