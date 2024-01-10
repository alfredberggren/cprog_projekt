#ifndef FOOD_H
#define FOOD_H
#include <string>

#include "Sprite.h"
#include "Player.h"

class Food : public Sprite {
   public:
    static Food* get_instance(std::string path, int x, int y, int w, int h);

    void tick() {}
    void mouseMoved(double x, double y) {}
    void kill(Sprite* killed_by = nullptr);
   private:
    Food(std::string path, int x, int y, int w, int h);
   

};

#endif  // FOOD_H