#include "Sprite.h"
#include "AssetManager.h"
#include "System.h"
#include <iostream>

Sprite::Sprite(std::string path_to_texture, int x, int y, int width, int height) : rect{x, y, width, height} {
    texture = AssetManager::get_instance()->loaded_textures[path_to_texture];
    if (texture == nullptr){
        std::cerr << "Texture could not be found when creating sprite" << std::endl;
    }
}

void Sprite::draw() {
    if (texture == nullptr) {
        std::cerr << "Texture is nullptr" << std::endl;
    }
    
    if (SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &rect) < 0) {
        std::cerr << "Sprite could not rendercopy" << std::endl;
        std::cerr << "Error: " << SDL_GetError() << std::endl;
    }
}


void Sprite::move(int x, int y) {
    rect.x += x;
    rect.y += y;
}

void Sprite::setX(int x) {
    rect.x = x;
}

void Sprite::setY(int y) {
    rect.y = y;
}

Sprite::~Sprite() {}
