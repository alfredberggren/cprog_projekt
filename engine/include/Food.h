#ifndef FOOD_H
#define FOOD_H
#include <string>

#include "Sprite.h"
#include "Player.h"

class Food : public Sprite {
   public:
    Food(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h, true) {}

    void tick() {}
    void mouseMoved(double x, double y) {}
    void kill(Sprite* killed_by = nullptr);
   

};

#endif  // FOOD_H