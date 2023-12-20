#include "SpriteManager.h"

SpriteManager::SpriteManager() {
    // Constructor implementation
    // Initialize the sprite vector
}

SpriteManager::~SpriteManager() {
    for (auto pair : loadedTextures) {
        delete pair.second;
    }
}

void SpriteManager::add(Sprite sprite) {
    sprites.push_back(&sprite);
}