#ifndef NPC_H
#define NPC_H
#include <string>
#include "Character.h"

class NPC : public Character {
    public:
        NPC(std::string path, int x, int y, int w, int h)
            : Character(path, x, y, w, h) {}

        void tick();

    private:

};

#endif  // NPC.H