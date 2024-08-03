#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

// Main function
int main(int argc, char *args[])
{

    // -----------   constants   ---------

    //   SDL init flags
    const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_TIMER;

    //   window context options
    const char* WINDOW_TITLE = "Hello world";
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const int WINDOW_X_POS = SDL_WINDOWPOS_CENTERED;
    const int WINDOW_Y_POS = SDL_WINDOWPOS_CENTERED;
    const Uint32 WINDOW_FLAGS = 0;

    //   delay option
    const int DELAY_TIME = 5000;

    // ------------------------------------

    // Store the window context
    SDL_Window *window = NULL;

    // Initialise the sdl context
    if (SDL_Init(SDL_INIT_FLAGS) != 0)
    {

        // Print the error to the console
        printf("error initialising SDL: %s\n", SDL_GetError());

        // Exit with an error code of 1
        return 1;
    }

    // Inistalise the sdl window
    // Link https://wiki.libsdl.org/SDL2/SDL_CreateWindow
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);

    // Check if window is null
    if (!window)
    {
        // Print the error to the console
        printf("error creating window: %s\n", SDL_GetError());

        // Quit SDL
        SDL_Quit();

        // Exit with an error code of 1
        return 1;
    }

    // Wait for a delay
    SDL_Delay(DELAY_TIME);

    // We are now down tell SDL to clean up the window
    SDL_DestroyWindow(window);

    // Tell SDL to quit
    SDL_Quit();

    // Exit with an error code of 0
    return 0;
}
