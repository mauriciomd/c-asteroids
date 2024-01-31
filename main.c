#include <stdbool.h>
#include <SDL2/SDL_image.h>

#include "internal/app.h"


int main(int argc, char* argv[]) {
    app_t *app = init_app(1280, 720);
    
    run_app(app);
    // init_SDL(&window);
    // load_sprites(&window);

    // SDL_FillRect(window.surface, NULL, SDL_MapRGB( window.surface->format, 0x00, 0x0, 0x0));

    // SDL_UpdateWindowSurface(window.w);
    
    //Clear screen
    // SDL_RenderClear(window.renderer);

    //Render texture to screen
    // SDL_RenderCopy(window.renderer, window.texture, NULL, NULL);

    //Update screen
    // SDL_RenderPresent(window.renderer);

    // SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    // SDL_Delay(10000);

    // SDL_DestroyWindow(window.w);
    // SDL_Quit();

    return 0;
}