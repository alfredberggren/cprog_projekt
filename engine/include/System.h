#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class System {
   private:
    static System* instance;
    SDL_Renderer* renderer;
    SDL_Window* window;
    System(/* args */);

   public:
    static System* get_instance() {
        if (instance == nullptr) {
            instance = new System();
        }
        return instance;
    }
    ~System();
};

#endif  // SYSTEM_H