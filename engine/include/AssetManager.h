#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Sprite.h"

class AssetManager
{
private:
    static AssetManager* instance;

    AssetManager();

    std::vector<Sprite*> sprites;

public:
    static std::unordered_map<std::string, SDL_Texture *> loaded_textures;
    static std::unordered_map<std::string, Mix_Chunk*> loaded_sounds;

    static AssetManager* get_instance()
    {
        if (instance == nullptr)
        {
            instance = new AssetManager();
            std::cout << "Created AssetManager" << std::endl;
        }
        return instance;
    }
    void add(Sprite&);

    void drawAll();
    ~AssetManager();
};

#endif // ASSET_MANAGER_H