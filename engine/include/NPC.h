#ifndef NPC_H
#define NPC_H
#include <string>

#include "Character.h"

class NPC : public Character {
   public:
    NPC(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {}

    void tick();
    // Flyttar NPC:n mot närmsta sprite som är mindre än sig själv
    void move_to_closest();
    void mouseMoved(double x, double y);

   private:
};

#endif  // NPC.H