#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// initialize SDL Video
bool init();

// load media
bool load_media();

// load a texture
SDL_Texture* load_texture(std::string path);

// deallocate memory
void close();

// window to be rendered to
SDL_Window* window = NULL;

// texture
SDL_Texture* texture = NULL;

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
            else
            {
                // intitialize png loading
                int flag = IMG_INIT_PNG;
                if (!(IMG_Init(flag) & flag))
                {
                    printf("Error initializing SDL_image for PNGs, %s\n", IMG_GetError());
                    success = false;
                }
            }
        }

        return success;
    }
}

SDL_Texture* load_texture(std::string path)
{
    // create texture
    SDL_Texture* new_texture = NULL;

    // load image to surface
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        printf("Error loading image to surface, %s\n", IMG_GetError());
    }
    else
    {
        // convert surface to texture
        new_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (new_texture == NULL)
        {
            printf("Error loading surface to texture, %s\n", SDL_GetError());
        }

        // deallocate the surface
        SDL_FreeSurface(surface);
    }

    return new_texture;
}

bool load_media()
{
    bool success = true;

    texture = load_texture("./duck.png");
    if (texture == NULL)
    {
        printf("Error loading the texture\n");
        success = false;
    }

    return success;
}

void close()
{
    // deallocate the texture
    SDL_DestroyTexture(texture);
    texture = NULL;

    // deallocate the window and renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    // quit the subsystems
    IMG_Quit();
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
        if (!load_media())
        {
            printf("Error loading media\n");
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

                // set up and draw top_left_viewport
                SDL_Rect top_left_viewport = {0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
                SDL_RenderSetViewport(renderer, &top_left_viewport);
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                // set up and draw top_right_viewport
                SDL_Rect top_right_viewport = {WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
                SDL_RenderSetViewport(renderer, &top_right_viewport);
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                // set up and draw bottom_viewport
                SDL_Rect bottom_viewport = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
                SDL_RenderSetViewport(renderer, &bottom_viewport);
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                SDL_RenderPresent(renderer);
            }

            close();
        }
    }

    return 1;
}