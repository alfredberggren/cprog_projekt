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

void AssetManager::drawAll(){
    for (Sprite* sprite : sprites){
        sprite->draw();
    }
}

std::unordered_map<std::string, SDL_Texture *> AssetManager::loaded_textures;
std::unordered_map<std::string, Mix_Chunk *> AssetManager::loaded_sounds;

AssetManager* AssetManager::instance;