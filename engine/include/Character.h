#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

#include "Sprite.h"

// Representerar karaktärer som rör på sig, spelbara eller inte.
class Character : public Sprite {
   public:
    Character(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h, true) {}
    virtual void tick() = 0;
    virtual void expand(int w, int h);
    virtual void minimize();
    void handle_collision();
    void move_to_point(double x, double y);
    double get_vel() const;
    virtual ~Character() {}
};

#endif