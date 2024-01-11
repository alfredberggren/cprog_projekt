#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>
#define PI 3.14

// TODO : Bör vara abstrakt?

class Sprite
{
private:
       Sprite &operator=(const Sprite &other) = delete;
       Sprite(const Sprite &other) = delete;

protected:
       Sprite(std::string path_to_texture, int x, int y, int width, int height,
              bool is_collideable);
       
       bool collidable; // TODO: check spelling on collidEable/collidable
       bool to_be_removed = false;
       bool to_be_relocated = false;
       bool followed_by_camera = false;
       SDL_Texture *texture;

public:
       SDL_Rect rect;
       static SDL_Rect camera;
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
       bool is_to_be_removed() const;
       void set_remove(bool remove);
       bool is_to_be_relocated() const;
       void set_relocate(bool relocate);
       void set_followed_by_camera(bool follow);

       virtual void kill(Sprite *killed_by) = 0;

       /*implement what to do when reacting to mouse-movement*/
       virtual void mouseMoved(double x, double y) = 0;

       virtual ~Sprite();
       virtual void draw();

       /*Implement what to do when not reacting to input*/
       virtual void tick() = 0;
};

#endif // SPRITE_H