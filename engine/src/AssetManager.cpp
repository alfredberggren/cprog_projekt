#include "AssetManager.h"

AssetManager::AssetManager() {
    // Constructor implementation
    // Initialize the sprite vector
}

AssetManager::~AssetManager() {
    std::cout << "Destroying AssetManager" << std::endl;
    for (auto pair : loaded_textures) {
        SDL_DestroyTexture(pair.second); 
    }
}

void AssetManager::add(Sprite& sprite) {
    sprites.push_back(&sprite);
}

void AssetManager::remove(Sprite& sprite) {
    for (int i = 0; i < sprites.size(); i++) {
        if (sprites[i] == &sprite) {
            sprites.erase(sprites.begin() + i);
            return;
        }
    }
}

void AssetManager::tickAll(){
    for (Sprite* sprite : sprites) {
        sprite->tick();
    }
}

void AssetManager::mouseMovedAll(double x, double y){
    for (Sprite* sprite : sprites) {
        sprite->mouseMoved(x, y);
    }
}



void AssetManager::drawAll(){
    for (Sprite* sprite : sprites){
        sprite->draw();
    }
}

std::unordered_map<std::string, SDL_Texture *> AssetManager::loaded_textures;
std::unordered_map<std::string, Mix_Chunk *> AssetManager::loaded_sounds;

AssetManager* AssetManager::instance;