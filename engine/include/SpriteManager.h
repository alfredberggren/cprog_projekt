#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "Sprite.h"

class SpriteManager {
   private:
    static SpriteManager* instance;
    SpriteManager();
    std::vector<Sprite*> sprites;

   public:
    static std::unordered_map<std::string, SDL_Texture*> loadedTextures;
    static SpriteManager* get_instance() {
        if (instance == nullptr) {
            instance = new SpriteManager();
        }
        return instance;
    }
    void add(Sprite);
    ~SpriteManager();
};

#endif  // SPRITE_MANAGER_H