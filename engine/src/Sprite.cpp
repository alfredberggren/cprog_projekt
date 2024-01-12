#include "Sprite.h"

#include <iostream>

#include "AssetManager.h"
#include "GameEngine.h"
#include "System.h"

Sprite::~Sprite() {
    
}

Sprite::Sprite(std::string path_to_texture, int x, int y, int width, int height,
               bool is_collideable)
    : rect{x, y, width, height}, collidable(is_collideable) {
    texture = AssetManager::get_instance()->get_texture(path_to_texture);
    if (texture == nullptr) {
        //std::cerr << "Texture could not be found when creating sprite"
         //         << std::endl;
    }
}

void Sprite::draw() const {

    if (texture == nullptr) {
        std::cerr << "Texture is nullptr" << std::endl;
    }
    SDL_Rect render_rect = {get_rendered_x(), get_rendered_y(),
                            get_rendered_w(), get_rendered_h()};
    SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &render_rect);
}

int Sprite::get_rendered_w() const { return getW(); }
int Sprite::get_rendered_h() const { return getH(); }
int Sprite::get_rendered_x() const { return rect.x; }
int Sprite::get_rendered_y() const { return rect.y; }

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
const SDL_Rect* Sprite::get_rect() const { return &rect; }

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

bool Sprite::is_to_be_removed() const { return to_be_removed; }

void Sprite::set_remove(bool remove) { to_be_removed = remove; }