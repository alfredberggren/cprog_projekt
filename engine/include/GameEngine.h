#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "System.h"
#include <SDL2/SDL.h>

class GameEngine {
   private:
    static GameEngine* instance;
    GameEngine(/* args */);

   public:
   void run_game();
    static GameEngine* get_instance() {
        if (instance == nullptr) {
            instance = new GameEngine();
        }
        return instance;
    }
    ~GameEngine();
};

#endif  // GAME_ENGINE_H