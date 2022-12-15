#include <SDL2/SDL.h>
#include <string>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

// constants for key presses
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


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

// the surfaces/images that correspond to key presses
// storage array
SDL_Surface* surface_array[KEY_PRESS_SURFACE_TOTAL];

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
        window = SDL_CreateWindow("Key Presses",SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,
                                   WINDOW_HEIGHT,0);

        // check to see if created
        if (window == NULL)
        {
            printf("Error creating window: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // get the window's surface
            window_surface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool load_media()
{
    bool success = true;

    // load default image
    surface_array[KEY_PRESS_SURFACE_DEFAULT] = load_surface("key-press-pics/cat1.bmp");
    if (surface_array[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Error loading media 1: %s\n", SDL_GetError());
        success = false;
    }

    // load up image
    surface_array[KEY_PRESS_SURFACE_UP] = load_surface("key-press-pics/cat2.bmp");
    if (surface_array[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Error loading media 2: %s\n", SDL_GetError());
        success = false;
    }

    // load down image
    surface_array[KEY_PRESS_SURFACE_DOWN] = load_surface("key-press-pics/cat3.bmp");
    if (surface_array[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Error loading media 3: %s\n", SDL_GetError());
        success = false;
    }

    // load left image
    surface_array[KEY_PRESS_SURFACE_LEFT] = load_surface("key-press-pics/cat4.bmp");
    if (surface_array[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Error loading media 4: %s\n", SDL_GetError());
        success = false;
    }

    // load right image
    surface_array[KEY_PRESS_SURFACE_RIGHT] = load_surface("key-press-pics/cat5.bmp");
    if (surface_array[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Error loading media 5: %s\n", SDL_GetError());
        success = false;
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

SDL_Surface* load_surface(std::string path)
{
    SDL_Surface* opt_surface = NULL;

    SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("Issue loading surface from path, %s\n", SDL_GetError());
    }
    else
    {
        opt_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, 0);
        if (opt_surface == NULL)
        {
            printf("Issue performing convert surface function using image %s, %s\n", path.c_str(), SDL_GetError());
        }

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

    current_surface = surface_array[KEY_PRESS_SURFACE_DEFAULT];

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
            else if (e.type = SDL_KEYDOWN)
            {
                // select image based on key press
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                    current_surface = surface_array[KEY_PRESS_SURFACE_UP];
                    break;

                    case SDLK_DOWN:
                    current_surface = surface_array[KEY_PRESS_SURFACE_DOWN];
                    break;

                    case SDLK_LEFT:
                    current_surface = surface_array[KEY_PRESS_SURFACE_LEFT];
                    break;

                    case SDLK_RIGHT:
                    current_surface = surface_array[KEY_PRESS_SURFACE_RIGHT];
                    break;

                    default:
                    current_surface = surface_array[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        SDL_Rect stretch_rect;
        stretch_rect.x = 0;
        stretch_rect.y = 0;
        stretch_rect.w = WINDOW_WIDTH;
        stretch_rect.h = WINDOW_HEIGHT;

        SDL_BlitScaled(current_surface, NULL, window_surface, &stretch_rect);

        // update the window with the new image
        SDL_UpdateWindowSurface(window);
    }

    // clean up
    close();
}
