#include <SDL2/SDL.h>
#include <thread>

// make the window and surfaces
SDL_Window* window = NULL;
SDL_Surface* window_surf = NULL;
SDL_Surface* image_surf = NULL;

bool init()
{
    bool success = true;
    
    // intitialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // create the window, fullscreen and centered
        window = SDL_CreateWindow("Cat Window :3",SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,SDL_WINDOW_FULLSCREEN,
                                    SDL_WINDOW_FULLSCREEN,NULL);
        
        // check to see if window created successfully
        if (window == NULL)
        {
            printf("Error creating window: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // get the window surface
            window_surf = SDL_GetWindowSurface(window);
        }
    }
    
    return success;
}

bool load_media(int cat_number)
{
    // init values
    bool success = true;
    char int_char = '0' + cat_number;
    char int_char2[] = {int_char};
    char first_part[30] = "cat-pics/cat";
    strcat(first_part,int_char2);
    char second_part[10] = ".bmp";
    strcat(first_part,second_part);
    
    // load the passed cat image
    image_surf = SDL_LoadBMP("cat1.bmp");

    // check to see if image is loaded
    if (image_surf == NULL)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

void close()
{
    // deallocate image surface
    SDL_FreeSurface(image_surf);
    image_surf = NULL;

    // destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // clean up intitialized sub-systems
    SDL_Quit();
}

void event_handler()
{
    bool quit = false;
    SDL_Event e;

    while (quit == false)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    
    // close the window and terminate the resources
    close();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        printf("Failed to initialize\n");
    }
    else
    {
        // create thread to handle closing event
        //std::thread poll_thread(event_handler); 

        // perform the loop for infinite iterations
        //while (1)
        //{
            //for (int i = 1; i < 6; i++)
            //{
                if (!load_media(0))
                {
                    printf("Failed to load media\n");
                }   
                else
                {
                    SDL_BlitSurface(image_surf,NULL,window_surf,NULL);
                    SDL_UpdateWindowSurface(window);
                }
                while (1);
                {}
            //}
        //}
    }
}