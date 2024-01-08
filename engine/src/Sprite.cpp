#include "Sprite.h"

#include <iostream>

#include "AssetManager.h"
#include "System.h"

Sprite::Sprite(std::string path_to_texture, int x, int y, int width, int height)
    : rect{x, y, width, height} {
    texture = AssetManager::get_instance()->loaded_textures[path_to_texture];
    if (texture == nullptr) {
        std::cerr << "Texture could not be found when creating sprite"
                  << std::endl;
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

void Sprite::move(double x, double y) {
    rect.x += x;
    rect.y += y;
}

void Sprite::setW(int w){
    rect.w += w;
}

void Sprite::setH(int h){
    rect.h = h;
}

void Sprite::setX(int x) {
    rect.x = x;
}

void Sprite::setY(int y) { rect.y = y; }

int Sprite::getCenterX() const { return rect.x + rect.w / 2; }

int Sprite::getCenterY() const { return rect.y - rect.h / 2; }

bool Sprite::isCollidable() const { return collidable; }

Sprite::~Sprite() {}
