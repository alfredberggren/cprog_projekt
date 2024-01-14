#include "GlobuleGobbleSprite.h"

GlobuleGobbleSprite::GlobuleGobbleSprite(std::string path_to_texture, int x, int y, int width,
                        int height, bool is_collidable)
        : Sprite(path_to_texture, x, y, width, height, is_collidable) {}

int GlobuleGobbleSprite::get_rendered_x() const {
    return get_rect()->x - Camera::get_instance()->get_x();
}

int GlobuleGobbleSprite::get_rendered_y() const {
    return get_rect()->y - Camera::get_instance()->get_y();
}