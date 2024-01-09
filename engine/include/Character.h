#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

#include "Sprite.h"

// Representerar karaktärer som rör på sig, spelbara eller inte.
class Character : public Sprite {
   public:
    Character(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h) {}
    virtual void tick() = 0;
    virtual void expand();
    virtual void minimize();
    void handle_collision();
    virtual ~Character() {}
};

#endif