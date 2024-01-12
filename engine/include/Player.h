#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <string>

#include "Character.h"

class Player : public Character {

   public:
    static Player* get_instance();

    void tick() override;
    void char_move() override;
    void mouse_moved(double x, double y) override;
    void boost_pressed();

   private:
    Player(std::string path, int x, int y, int w, int h);
    double mouse_x;
    double mouse_y;
    static Player* instance;
    double dir_to_mouse;
};

#endif  // PLAYER_H