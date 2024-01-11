#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <string>

#include "Character.h"

class Player : public Character {
    // TODO: singleton

   public:
    static Player* get_instance();

    void tick() override;
    void char_move() override;
    void mouseMoved(double x, double y) override;
    void boost_pressed();

   private:
    Player(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {
        followed_by_camera = true;
    }
    double mouse_x;
    double mouse_y;
    static Player* instance;
    double dir_to_mouse;
};

#endif  // PLAYER_H