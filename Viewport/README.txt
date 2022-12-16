Renders textures to three different viewports

The viewports are just portions of the screen that have been specified
by the programmer. Using these viewports, we copy the texture to the renderer
buffer with the set viewport. Then later after we specify all the viewports and
finally call RenderPresent, the textures will be rendered to their viewports. 
