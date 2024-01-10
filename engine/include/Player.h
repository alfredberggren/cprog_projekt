#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <string>

#include "Character.h"

class Player : public Character {
    // TODO: singleton

   public:
    static Player* get_instance();


    void tick();
    void moveToMouse();
    void mouseMoved(double x, double y);

   private:
    Player(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {}
    double mouse_x;
    double mouse_y;
    static Player* instance;
};





#endif  // PLAYER_H