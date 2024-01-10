#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <string>

#include "Character.h"

class Player : public Character {
    // TODO: singleton

   public:
    Player(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {}

    void tick();
    void move_toward_mouse();
    void center_camera();
    void mouseMoved(double x, double y);

   private:
    double mouse_x;
    double mouse_y;
    double dir_to_mouse;
};

#endif  // PLAYER_H