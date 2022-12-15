Changes images on window based on key presses (Optimized)

The program will open a window and intitialize a surface. This
surface can change based on a key press of left, right, up, or down. 
These images will be loaded to a specific member of a surface array 
with key press total size (5). The key press will correspond to a 
specific enum which is good practice for game development. KEY_PRESS_SURFACE_TOTAL 
is 5. The previous version was loading a 24 bitmap image to the hardware and was
needed to be converted to 32 bits each time it was loaded. In order to spare a lot of 
overhead time, we are adding the SDL_ConvertSurface function to load_surface to convert to 
a 32 bitmap image. This returns a new address so we need to deallocate the old address that
we allocated for the previous 24 bit address.
