#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Sprite.h"
#include "AssetManager.h"
#include "System.h"

class GameEngine {
   private:
    static GameEngine* instance;
    GameEngine(/* args */);
    
    bool load_img(std::string path);
    bool load_sound(std::string path);

   public:
    SDL_Texture* texture;
    
    void run_game();
    static GameEngine* get_instance() {
        if (instance == nullptr) {
            instance = new GameEngine();
        }
        return instance;
    }
    void load_assets(std::vector<std::string> assets);
    void loadSurface(std::string& asset, SDL_Surface* surface, int& retFlag);

    void add_sprite(Sprite& sprite);

    ~GameEngine();
};

#endif  // GAME_ENGINE_H