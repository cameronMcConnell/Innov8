#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// initialize SDL Video
bool init();

// deallocate memory
void close();

// window to be rendered to
SDL_Window* window = NULL;

// renderer
SDL_Renderer* renderer = NULL;

bool init()
{
    bool success = true;

    // initialize the SDL_video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL video subsystem, %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // create the window
        window = SDL_CreateWindow("Geometry Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        if (window == NULL)
        {
            printf("Error creating window, %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // create the renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Error creating renderer, %s\n", SDL_GetError());
                success = false;
            }
        }

        return success;
    }
}

void close()
{
    // deallocate the window and renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    // quit the subsystems
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        printf("Error initialzing SDL\n");
        return 0;
    }
    else
    {
        SDL_Event e;
        bool quit = false;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            // clear the screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            // create rectangle struct
            // values are x, y, w, h
            // point of origin is the top left and y increases going down rather than up
            SDL_Rect rectangle = {WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

            // set the draw color to red and fill the reactangle with red
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rectangle);

            // create a rect
            SDL_Rect rect_outline = {WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 2 / 3};

            // set the draw color to green and draw the rectangle rather than fill it
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer, &rect_outline);

            // draw a blue horizontal line
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);

            // draw a line of yellow vertical dots
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
            for (int i = 0; i < WINDOW_HEIGHT; i += 4)
            {
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, i);
            }

            // update the screen
            SDL_RenderPresent(renderer);
        }

        close();
    }

    return 1;
}