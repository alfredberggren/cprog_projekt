#include "Sprite.h"

#include <iostream>

#include "AssetManager.h"
#include "System.h"

SDL_Rect Sprite::camera = {0, 0, 640, 480};

Sprite::~Sprite() {}

Sprite::Sprite(std::string path_to_texture, int x, int y, int width, int height, bool is_collideable)
    : collidable(is_collideable), rect{x, y, width, height}  {
    texture = AssetManager::get_instance()->get_texture(path_to_texture);
    if (texture == nullptr) {
        std::cerr << "Texture could not be found when creating sprite"
                  << std::endl;
    }
}

void Sprite::draw() {
    if (texture == nullptr) {
        std::cerr << "Texture is nullptr" << std::endl;
    }

    //if (SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &rect) < 0) {
    //    std::cerr << "Sprite could not rendercopy" << std::endl;
    //    std::cerr << "Error: " << SDL_GetError() << std::endl;
    //}
    SDL_Rect renderQuad = {rect.x - camera.x, rect.y - camera.y, rect.w,
                           rect.h};

    SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &renderQuad);
}

void Sprite::move(double x, double y) {
    rect.x += x;
    rect.y += y;
}

void Sprite::setW(int w) { rect.w = w; }

void Sprite::setH(int h) { rect.h = h; }

void Sprite::setX(int x) { rect.x = x; }

void Sprite::setY(int y) { rect.y = y; }

int Sprite::getW() const { return rect.w; }

int Sprite::getH() const { return rect.h; }

int Sprite::getCenterX() const { return rect.x + rect.w / 2; }

int Sprite::getCenterY() const { return rect.y + rect.h / 2; }

bool Sprite::isCollidable() const { return collidable; }

int Sprite::area() const { return rect.w * rect.h; }

bool Sprite::to_remove() const { return to_be_removed; }

void Sprite::set_remove(bool remove) { to_be_removed = remove; }