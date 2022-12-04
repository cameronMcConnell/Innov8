# Innovation
**Goal:**
  - Implement a basic game engine that can be used to create 3D games.

## Implementations 
1. **Programming Language:**
   - C++
     - Required for low-level memory access as well as faster execution due to the language being compiled rather than interpreted. 
2. **Hardware Access:**
   - OS protects hardware from programmer.
   - Need API for multi-platform hardware abstraction.
   - 2D: SDL
   - 3D: GLFW
     - Works well with 3D API's like OpenGL and Vulkan.
3. **Game Loop:**
   - Handles input, updates game objects and their respected data, and renders objects on the screen.
   - Performs calculations so that frame rate does not affect game objects and their data differently on one system compared to another. 
4. **Input:**
   - Use of OS abstraction to determine what actions to take based on user input.
   - Implemented within the game loop.
   - What types of input will this engine support?
5. **Representing Objects in Memory:**
   - Data structures used to store and access objects within the game. 
   - Can use API to implement or our own using C++ standard template library.
   - Object Oriented approach with classes and inheritance or entities and components. 
     - Think of entities as the objects themselves while components are the data representations of all the different aspects that an entity may posses. 
   - Could use already implemented C++ ECS (Entity-Component-System) libraries for this implementation.
     - EnTT and FLECS.
6. **Rendering:**
   - Handle 3D rendering as well as managing a graphics pipeline for the GPU. 
     - OpenGL, Direct3D, Vulkan, Metal.
   - Need to implement a library that handles decoding different mesh formats.
     - TinyOBJLoader and AssImp.
7. **Physics:**
   - Given entities in our game, we want to be able to implement a library such that we can perform a physics simulation upon any object/entity.
   - A 3D physics library will be the focus. 
8. **UI:**
   - Implement a UI that can be used in a sandbox type environment to make altering entities seamless and easy.
     - DearImGui, Qt, and Nuklear. 
9. **Scripting:**
   - Will make use of a scripting language based within our C++ to make scripting enemy behavior, AI logic, animation, and other aspects simpler.
     - Also allows some aspects that are not required within the C++ libraries to be seperate such as AI. 
   - Will be using Lua due to its easy integration with C++ due to its interpreter being written in C.
10. **Audio:**
    - Need access to audio based hardware so their is a need for audio based OS APIs. 
      - SDL_Mixer, SoLoud, FMOD.
    - Will be implemented last probably.
11. **Artificial Intelligence:**
    - May or may not implement this part of the engine.
    - Will require knowledge on AI game design.
    - Will the engine require us to implement enemies or NPCs that require AI?
