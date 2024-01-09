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

    double getDirToMouse();
    void tick();
    void moveToMouse();
    void mouseMoved(double x, double y);

   private:
    double mouse_x;
    double mouse_y;
};

#endif  // PLAYER_H