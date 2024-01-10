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
    void move_toward_mouse();
    void center_camera();
    void mouseMoved(double x, double y);
    void boost_pressed();

   private:
    Player(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {}
    double mouse_x;
    double mouse_y;
    static Player* instance;
    double dir_to_mouse;
};





#endif  // PLAYER_H