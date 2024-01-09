#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

// TODO : Bör vara abstrakt?

class Sprite {
   private:
    bool collidable;
    SDL_Texture* texture;

   public:
    SDL_Rect rect;
    void move(double x, double y);
    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);
    int getW() const;
    int getH() const;
    int getCenterX() const;
    int getCenterY() const;
    int area() const;
    bool isCollidable() const;

    /*implement what to do when reacting to mouse-movement*/
    virtual void mouseMoved(double x, double y) = 0;
    
    Sprite(std::string path_to_texture, int x, int y, int width, int height);
    virtual ~Sprite();
    void draw();

    /*Implement what to do when not reacting to input*/
    virtual void tick() = 0;
};

#endif  // SPRITE_H