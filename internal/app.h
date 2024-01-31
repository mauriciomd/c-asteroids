#include <SDL2/SDL.h>
#include "../objects/spaceship.h"

typedef struct App {
    int screen_width;
    int screen_height;
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;

    spaceship_t* player; 
} app_t;

app_t* init_app(int width, int height);
void init_sdl(app_t* app);
void run_app(app_t *app);
void create_player(app_t* app);
void destroy_game_objects(app_t* app);