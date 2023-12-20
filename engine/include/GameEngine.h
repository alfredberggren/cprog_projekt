#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

class GameEngine {
   private:
    static GameEngine* instance;
    GameEngine(/* args */);

   public:
    static GameEngine* get_instance() {
        if (instance == nullptr) {
            instance = new GameEngine();
        }
        return instance;
    }
    ~GameEngine();
};

GameEngine::GameEngine() {
    
}

GameEngine::~GameEngine() {}

#endif  // GAME_ENGINE_H