#ifndef FOOD_H
#define FOOD_H
#include <string>

#include "GlobuleGobbleSprite.h"
#include "Player.h"

class Food : public GlobuleGobbleSprite {
   public:
    static Food* get_instance(std::string path, int x, int y, int w, int h);

    void tick() {}
    void mouse_moved(double x, double y) {}
    void die(Sprite& killed_by);
   private:
    Food(std::string path, int x, int y, int w, int h);
};

#endif  // FOOD_H