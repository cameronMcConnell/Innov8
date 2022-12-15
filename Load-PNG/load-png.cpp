#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// initializes sdl
bool init();

// loads the media to the surface
bool load_media();

// deallocates the SDL subsystems
void close();

// loads the individual media
SDL_Surface* load_surface(std::string path);

// window we are rendering to
SDL_Window* window = NULL;

// the surface contained by the window
SDL_Surface* window_surface = NULL;

// current image to be loaded on the window surface
SDL_Surface* current_surface = NULL; 

bool init()
{
    bool success = true;

    // start SDL subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        success = false;

    }
    else
    {
        // create a centered and fullscreen window
        window = SDL_CreateWindow("Load PNG",SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,1001,
                                   1001,0);

        // check to see if created
        if (window == NULL)
        {
            printf("Error creating window: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // intitialize SDL_image
            int int_flag = IMG_INIT_PNG;
            if (!(IMG_Init(int_flag) & int_flag))
            {
                printf("SDL_image could not be initialized, %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                // get the windows surface 
                window_surface = SDL_GetWindowSurface(window);
            }
        }
    }

    return success;
}

void close()
{
    // deallocate the current image
    SDL_FreeSurface(current_surface);
    current_surface = NULL;

    // destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // clean up initialized subsystems
    SDL_Quit();
}

bool load_media()
{
    bool success = true;

    current_surface = load_surface("./ILTQq.png");
    if (current_surface == NULL)
    {
        printf("Issue loading the image\n");
        success = false;
    }
    
    // upload the surface to the buffer
    SDL_BlitSurface(current_surface, NULL, window_surface, NULL);

    // update the window with the new image
    SDL_UpdateWindowSurface(window);

    return success;
}

SDL_Surface* load_surface(std::string path)
{
    // optimized surface
    SDL_Surface* opt_surface = NULL;

    // use IMG_Load to load the PNG 
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("Issue loading surface from path, %s\n", IMG_GetError());
    }
    else
    {
        // convert the surface
        opt_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, 0);
        if (opt_surface == NULL)
        {
            printf("Unable to optomize image %s, %s\n", path.c_str(), SDL_GetError());
        }

        // deallocate the previous surface
        SDL_FreeSurface(loaded_surface);
    }

    return opt_surface;
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        printf("Error in initializing SDL.\n");
        return 0;
    }
    else
    {
        if (!load_media())
        {
            printf("Failed to load media\n");
            return 0;
        }
    }
    
    // write the game loop. 
    bool quit = false;
    SDL_Event e;

    // game loop
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            // check if x is pressed
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // clean up
    close();
}
