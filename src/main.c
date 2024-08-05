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
        // Each of the following renders an octant of the circle
        // Link: https://wiki.libsdl.org/SDL2/SDL_RenderDrawPoint
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
    //Link: https://wiki.libsdl.org/SDL2/SDL_Init
    if (SDL_Init(SDL_INIT_FLAGS) != 0)
    {

        // Print the error to the console
        printf("error initialising SDL: %s\n", SDL_GetError());

        // Exit with an error code of 1 to indicate an error occured
        return 1;
    }

    // Inistalise the sdl window
    // Link: https://wiki.libsdl.org/SDL2/SDL_CreateWindow
    window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);

    // Check if window is null
    if (!window)
    {
        // Print the error to the console
        printf("error creating window: %s\n", SDL_GetError());

        // Quit SDL
        // Link: https://wiki.libsdl.org/SDL2/SDL_Quit
        SDL_Quit();

        // Exit with an error code of 1 to indicate an error occured
        return 1;
    }

    // Set up a renderer
    // Link: https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDER_FLAGS);

    // Check if the renderer was created successfully
    if (!renderer)
    {
        printf("error creating the renderer: %s\n", SDL_GetError());

        // We are now down tell SDL to clean up the window
        // Link: https://wiki.libsdl.org/SDL2/SDL_DestroyWindow
        SDL_DestroyWindow(window);

        // Tell SDL to quit
        // Link: https://wiki.libsdl.org/SDL2/SDL_Quit
        SDL_Quit();

        // Exit with an error code of 1 to indicate an error occured
        return 1;
    }

    // Set the FPS
    const int FPS = 120;

    // Set the size of the circle
    int size = 20;

    // Set the speed of the circle
    const int SPEED = 300;

    // Set the starting x pos of the circle
    float x_pos = 0 + size;

    // Set the starting y pos of the circle
    float y_pos = 0 + size;

    // Set the starting x velocity of the circle
    float x_vel = SPEED;

    // Set the starting y velocity of the circle
    float y_vel = SPEED;

    // Store running value
    int running = 1;

    // Loop while running is 1
    while (running)
    {

        // Store the SDL Event
        SDL_Event event;

        // Loop Polling the SDL events
        // Link: https://wiki.libsdl.org/SDL2/SDL_PollEvent
        while (SDL_PollEvent(&event))
        {

            // Check if the event type is Quit
            if (event.type == SDL_QUIT)
            {
                // Set the running value to 0 to exit
                running = 0;
            }
        }

        // Check lower bounds of the x pos
        if (x_pos <= 0 + size)
        {
            // Reset the x position
            x_pos = 0 + size;

            // Set the x velocity to negative
            x_vel = -x_vel;
        }

        // Check the upper bounds of the x pos
        if (x_pos >= WINDOW_WIDTH - size)
        {
            // Reset the x position
            x_pos = WINDOW_WIDTH - size;

            // Set the x velocity to negative
            x_vel = -x_vel;
        }

        // Check lower bounds of the y pos
        if (y_pos <= 0 + size)
        {
            // Reset the y position
            y_pos = 0 + size;

            // Set the y velocity to negative
            y_vel = -y_vel;
        }

        // Check the upper bounds of the y pos
        if (y_pos >= WINDOW_HEIGHT - size)
        {
            // Reset the y position
            y_pos = WINDOW_HEIGHT - size;

            // Set the y velocity to negative
            y_vel = -y_vel;
        }

        // Reset the draw colour to black
        // Link: https://wiki.libsdl.org/SDL2/SDL_SetRenderDrawColor
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        // Clear the renderer
        // Link: https://wiki.libsdl.org/SDL2/SDL_RenderClear
        SDL_RenderClear(renderer);

        // Set the renderer colour to read
        // Link: https://wiki.libsdl.org/SDL2/SDL_SetRenderDrawColor
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Draw a cirle
        DrawCircle(renderer, x_pos, y_pos, size);

        // Present what is int the renderer
        // Link: https://wiki.libsdl.org/SDL2/SDL_RenderPresent
        SDL_RenderPresent(renderer);

        // Set the x pos
        x_pos += x_vel / FPS;

        // Set the y pos
        y_pos += y_vel / FPS;

        // Set a delay of for 60fps
        // Link: https://wiki.libsdl.org/SDL2/SDL_Delay
        SDL_Delay(1000 / FPS);
    }

    // Clean up the renderer
    // Link: https://wiki.libsdl.org/SDL2/SDL_DestroyRenderer
    SDL_DestroyRenderer(renderer);

    // Clean up the window
    // Link: https://wiki.libsdl.org/SDL2/SDL_DestroyWindow
    SDL_DestroyWindow(window);

    // Tell SDL to quit
    // Link: https://wiki.libsdl.org/SDL2/SDL_Quit
    SDL_Quit();

    // Exit with an error code of 0
    return 0;
}
