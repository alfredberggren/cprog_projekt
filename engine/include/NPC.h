#ifndef NPC_H
#define NPC_H
#include <string>

#include "Character.h"

class NPC : public Character {
   public:
    static NPC* get_instance(std::string path, int x, int y, int w , int h);

    void tick() override;
    // NPC:s rörelse-algoritm
    void char_move() override;
    void mouseMoved(double x, double y);
    // Inverterar en riktning
    double inv_dir(double dir);
    enum class State { NERVOUS, HUNGRY, ANGRY };
    State state;
    // Radie runt NPC:n där den kan se mat
    static const int FOG_RADIUS = 250;

   private:
    NPC(std::string path, int x, int y, int w, int h);
};

#endif  // NPC.H