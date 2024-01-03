#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

class Sprite {
   private:
    SDL_Rect rect;
    bool collidable;
    SDL_Texture* texture;

   public:
    Sprite(std::string path_to_texture, int x, int y, int width, int height);
    ~Sprite();
    void draw();
};

#endif  // SPRITE_H