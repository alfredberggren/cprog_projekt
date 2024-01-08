#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Sprite.h"

typedef void (*funcPtr)(Sprite*);

class AssetManager
{
private:
    static AssetManager* instance;

    AssetManager();

   public:
    std::vector<Sprite*> sprites;
    static std::unordered_map<std::string, SDL_Texture*> loaded_textures;
    static std::unordered_map<std::string, Mix_Chunk*> loaded_sounds;

    static AssetManager* get_instance() {
        if (instance == nullptr) {
            instance = new AssetManager();
            std::cout << "Created AssetManager" << std::endl;
        }
        return instance;
    }

    void handleKeyEvent(funcPtr func);

    void add(Sprite&);

    void remove(Sprite&);

    void tickAll();

    void mouseMovedAll(double, double);

    void drawAll();
    ~AssetManager();
};

#endif  // ASSET_MANAGER_H