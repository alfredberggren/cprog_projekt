#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class System {
   public:
    bool initSDLComponents();
    bool initWindowAndRenderer(std::string title, int xPos, int yPos, int width, int height);
    SDL_Renderer* renderer;
    SDL_Window* window;
    System();
    ~System();
};

extern System SYSTEM;

#endif  // SYSTEM_H