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
SDL_Texture* load_texture(std::string path);

// window we are rendering to
SDL_Window* window = NULL;

// renderer used to render images to a window
SDL_Renderer* renderer = NULL;

// used to create a texture from a loaded image
SDL_Texture* texture = NULL;

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
        window = SDL_CreateWindow("Texture Render",SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,1920,
                                   1080,0);

        // check to see if created
        if (window == NULL)
        {
            printf("Error creating window: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // create an accelerated renderer I guess
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Error creating the renderer, %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // set the base drawing color of the render to white
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // intitialize SDL_image
                int int_flag = IMG_INIT_PNG;
                if (!(IMG_Init(int_flag) & int_flag))
                {
                    printf("SDL_image could not be initialized, %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void close()
{
    // deallocate the current image
    SDL_DestroyTexture(texture);
    texture = NULL;

    // destroy window & renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    // clean up initialized subsystems
    IMG_Quit();
    SDL_Quit();
}

bool load_media()
{
    bool success = true;

    texture = load_texture("./duck.png");
    if (texture == NULL)
    {
        printf("Issue loading the texture\n");
        success = false;
    }
    
    return success;
}

SDL_Texture* load_texture(std::string path)
{
    // optimized surface
    SDL_Texture* new_texture = NULL;

    // use IMG_Load to load the PNG 
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("Issue loading surface from path, %s\n", IMG_GetError());
    }
    else
    {
        // load a texture from an existing surface
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (new_texture == NULL)
        {
            printf("Error loading texture from surface, %s\n", SDL_GetError());
        }

        // deallocate the loaded surface
        SDL_FreeSurface(loaded_surface);
    }

    return new_texture;
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

        // clear the screen
        SDL_RenderClear(renderer);

        // copy the texture to the renderer/window buffer
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // display the texture
        SDL_RenderPresent(renderer);
    }

    // clean up
    close();
}
