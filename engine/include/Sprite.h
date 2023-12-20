#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

class Sprite {
   private:
    SDL_Rect rect;
    bool collidable;

   public:
    Sprite(int x, int y, int width, int height);
    ~Sprite();
};

#endif  // SPRITE_H