#ifndef FOOD_H
#define FOOD_H
#include <string>

#include "Sprite.h"

class Food : public Sprite {
   public:
    Food(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h) {}

    void tick() {}
    void mouseMoved(double x, double y) {}

   private:
    int value = 5;
};

#endif  // FOOD_H