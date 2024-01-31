#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../objects/spaceship.h"

typedef struct KeyPressed {
    bool is_left_pressed;
    bool is_right_pressed;
    bool is_up_pressed;
} keypressed_t;

typedef struct App {
    bool is_running;

    int screen_width;
    int screen_height;
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    keypressed_t keys;
    
    spaceship_t* player; 
} app_t;

app_t* init_app(int width, int height);
void init_sdl(app_t* app);
void run_app(app_t *app);
void create_player(app_t* app);
void process_events(SDL_Event event, app_t* app);
void process_scene(app_t* app);
void render_objects(app_t* app);
void destroy_game_objects(app_t* app);