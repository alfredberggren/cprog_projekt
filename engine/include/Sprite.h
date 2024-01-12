#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>

#define PI 3.14


class Sprite {
   private:
    Sprite &operator=(const Sprite &other) = delete;
    Sprite(const Sprite &other) = delete;
    SDL_Rect rect;

    // Subklasser av sprite kan överlagra dessa för att specificera hur deras
    // storlek och position ska renderas.
    virtual int get_rendered_w() const;
    virtual int get_rendered_h() const;
    virtual int get_rendered_x() const;
    virtual int get_rendered_y() const;

   protected:
    SDL_Texture *texture;  // WARNING! SHOULD MAYBE BE PRIVATE?!
    bool collidable;

    Sprite(std::string path_to_texture, int x, int y, int width, int height,
           bool is_collidable);

    bool to_be_removed = false;

   public:
    const SDL_Rect *get_rect() const;
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

    /*implement what to do when reacting to mouse-movement*/
    virtual void mouse_moved(double x, double y) = 0;


    virtual ~Sprite();
    virtual void draw() const;

    /*Implement what to do when not reacting to input*/
    virtual void tick() = 0;
};

#endif  // SPRITE_H