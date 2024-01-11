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
       SDL_Rect rect;
       

protected:
       bool collidable; 
       SDL_Texture *texture; //WARNING! SHOULD MAYBE BE PRIVATE?!
       

       Sprite(std::string path_to_texture, int x, int y, int width, int height, bool is_collidable);
       
       bool to_be_removed = false;
       bool to_be_relocated = false;
       bool followed_by_camera = false;
       

public:
       static SDL_Rect camera;
       const SDL_Rect* get_rect() const;
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

       /*implement what to do when reacting to mouse-movement*/
       virtual void mouse_moved(double x, double y) = 0;

       virtual ~Sprite();
       virtual void draw() const;

       /*Implement what to do when not reacting to input*/
       virtual void tick() = 0;
};

#endif // SPRITE_H