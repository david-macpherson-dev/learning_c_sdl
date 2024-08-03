#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

// Main function
int main(int argc, char *args[])
{

    // -----------   constants   ---------

    //   SDL init flags
    const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_TIMER;

    //   window context options
    const char *WINDOW_TITLE = "Hello world";
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const int WINDOW_X_POS = SDL_WINDOWPOS_CENTERED;
    const int WINDOW_Y_POS = SDL_WINDOWPOS_CENTERED;
    const Uint32 WINDOW_FLAGS = 0;

    //   delay option
    const int DELAY_TIME = 5000;

    //    render Flags
    const Uint32 RENDER_FLAGS = SDL_RENDERER_ACCELERATED;

    // ------------------------------------

    // Store the window context
    SDL_Window *window = NULL;

    // Initialise the sdl context
    if (SDL_Init(SDL_INIT_FLAGS) != 0)
    {

        // Print the error to the console
        printf("error initialising SDL: %s\n", SDL_GetError());

        // Exit with an error code of 1 to indicate an error occured
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

        // Exit with an error code of 1 to indicate an error occured
        return 1;
    }

    // Set up a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDER_FLAGS);

    // Check if the renderer was created successfully
    if (!renderer)
    {
        printf("error creating the renderer: %s\n", SDL_GetError());

        // We are now down tell SDL to clean up the window
        SDL_DestroyWindow(window);

        // Tell SDL to quit
        SDL_Quit();

        // Exit with an error code of 1 to indicate an error occured
        return 1;
    }

    int x_pos = 0;
    int y_pos = 0;
    int size = 20;

    // Store running value
    int running = 1;

    // Loop while running is 1
    while (running)
    {

        // Store the SDL Event
        SDL_Event event;
        // Loop Polling the SDL events
        while (SDL_PollEvent(&event))
        {

            // Check if the event type is Quit
            if (event.type == SDL_QUIT)
            {
                // Set the running value to 0 to exit
                running = 0;
            }
        }

        // Reset the draw colour to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Set the renderer colour to read
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw a cirle
        DrawCircle(renderer, x_pos, y_pos, size);

        // Present what is int the renderer
        SDL_RenderPresent(renderer);

        // Set a delay of for 60fps
        SDL_Delay(1000 / 60);

        // Increment the x_pos and y_pos by 1
        x_pos += 1;
        y_pos += 1;
    }

    // Clean up the renderer
    SDL_DestroyRenderer(renderer);

    // Clean up the window
    SDL_DestroyWindow(window);

    // Tell SDL to quit
    SDL_Quit();

    // Exit with an error code of 0
    return 0;
}
