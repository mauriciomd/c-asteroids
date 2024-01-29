#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Window {
    int width;
    int height;
    SDL_Window *w;
    SDL_Surface *surface;
    SDL_Renderer *renderer;

} window_t;

void init_SDL(window_t *window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initializes. Error: %s", SDL_GetError());
        exit(1);
    }

    window->w = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width, window->height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (window->w == NULL) {
        printf("SDL Window could not be created. Error: %s", SDL_GetError());
        exit(1);
    }

    window->surface = SDL_GetWindowSurface(window->w);
}

int main(int argc, char* argv[]) {
    window_t window = { 1280, 720, NULL, NULL, NULL };
    
    init_SDL(&window);

    SDL_FillRect(window.surface, NULL, SDL_MapRGB( window.surface->format, 0x00, 0x0, 0x0));

    SDL_UpdateWindowSurface(window.w);
    
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    SDL_DestroyWindow(window.w);
    SDL_Quit();

    return 0;
}