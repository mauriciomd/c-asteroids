#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "internal/app.h"


int main(int argc, char* argv[]) {
    srand((unsigned) time(NULL)); 

    app_t *app = init_app(1280, 720);
    run_app(app);
    
    return 0;
}