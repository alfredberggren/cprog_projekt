#ifndef NPC_H
#define NPC_H
#include <string>

#include "Character.h"

enum class State { NERVOUS, HUNGRY, ANGRY };

class NPC : public Character {
   public:
    // Radie runt NPC:n där den kan se mat
    static const int FOG_RADIUS = 200;
    // Radier runt NPC där den kommer att använda boost defensivt eller aggressivt. 
    static const int ESCAPE_BOOST_RADIUS = 100;
    static const int ATTACK_BOOST_RADIUS = 500;

    static NPC* get_instance(std::string path, int x, int y, int w , int h);

    void tick() override;
    // NPC:s rörelse-algoritm
    void char_move() override;
    void mouse_moved(double x, double y) override {}
   
    State get_state() const;

   private:
    NPC(std::string path, int x, int y, int w, int h);
    State state;
    // Inverterar en riktning
    double inv_dir(double dir);
};

#endif  // NPC.H