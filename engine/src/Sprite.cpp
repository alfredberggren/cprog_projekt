#include "Sprite.h"

#include <iostream>

#include "AssetManager.h"
#include "GameEngine.h"
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
    //SDL_SetRenderDrawColor(SYSTEM.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //SDL_RenderFillRect(SYSTEM.renderer, &camera);
    //SDL_SetRenderDrawColor(SYSTEM.renderer, 0x00, 0x00, 0x00, 0x00);

    //if (SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &rect) < 0) {
    //    std::cerr << "Sprite could not rendercopy" << std::endl;
    //    std::cerr << "Error: " << SDL_GetError() << std::endl;
    //}

    
    SDL_Rect render_rect = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
    SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &render_rect);
}

void Sprite::move(double x, double y) {
    rect.x += x;
    rect.y += y;
    if (rect.x < 0) {
        rect.x = 0;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    if (rect.x > 3500 - rect.w) {
        rect.x = 3500 - rect.w;
    }
    if (rect.y > 3500 - rect.h) {
        rect.y = 3500 - rect.h;
    }
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

int Sprite::area() const{ return rect.w * rect.h; }

bool Sprite::is_to_be_removed() const { return to_be_removed; }

void Sprite::set_remove(bool remove) { to_be_removed = remove; }

bool Sprite::is_to_be_relocated() const { return to_be_relocated; }

void Sprite::set_relocate(bool relocate) { to_be_relocated = relocate; }

void Sprite::set_followed_by_camera(bool follow) { followed_by_camera = follow; }