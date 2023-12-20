#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Sprite.h"
#include "SpriteManager.h"
#include "System.h"

class GameEngine {
   private:
    static GameEngine* instance;
    GameEngine(/* args */);
    void loadPng(std::string path);
    void loadJpg(std::string path);
    void loadMp3(std::string path);
    void loadWav(std::string path);

   public:
    void run_game();
    static GameEngine* get_instance() {
        if (instance == nullptr) {
            instance = new GameEngine();
        }
        return instance;
    }
    void load_assets(std::vector<std::string> assets);
    void loadSurface(std::string& asset, SDL_Surface* surface, int& retFlag);
    ~GameEngine();
};

#endif  // GAME_ENGINE_H