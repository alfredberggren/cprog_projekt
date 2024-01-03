#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class System {
  
   public:
    bool initSDLComponents();
    SDL_Renderer* renderer;
    SDL_Window* window;
    System();
    ~System();
};

extern System SYSTEM;

#endif  // SYSTEM_H