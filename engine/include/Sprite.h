#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

// TODO : Bör vara abstrakt?

class Sprite {
   private:
    SDL_Rect rect;
    bool collidable;
    SDL_Texture* texture;

   public:
    void move(int x, int y);
    void setX(int x);
    void setY(int y);

    /*implement what to do when reacting to mouse-movement*/
    virtual void mouseMoved(int x, int y) = 0;
    
    Sprite(std::string path_to_texture, int x, int y, int width, int height);
    ~Sprite();
    void draw();

    /*Implement what to do when not reacting to input*/
    virtual void tick() = 0;
};

#endif  // SPRITE_H