#ifndef NPC_H
#define NPC_H
#include <string>

#include "Character.h"

class NPC : public Character {
   public:
    NPC(std::string path, int x, int y, int w, int h)
        : Character(path, x, y, w, h) {}

    void tick() override;
    // Flyttar NPC:n mot närmsta sprite som är mindre än sig själv
    void char_move() override;
    void mouseMoved(double x, double y);
    enum class State { NERVOUS, HUNGRY, ANGRY };
    State state;
    // Radie runt NPC:n där den kan se mat
    static const int FOG_RADIUS = 250;

   private:
};

#endif  // NPC.H