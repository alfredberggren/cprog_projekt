#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class System {
   private:
    static System* instance;
    void initSDLComponents();

   public:
    System();
    SDL_Renderer* renderer;
    SDL_Window* window;
    ~System();
};

extern System sys;

#endif  // SYSTEM_H