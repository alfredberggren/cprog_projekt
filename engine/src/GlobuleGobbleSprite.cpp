#include "GlobuleGobbleSprite.h"

int GlobuleGobbleSprite::get_rendered_x() const {
    return get_rect()->x - Camera::get_instance()->get_x();
}

int GlobuleGobbleSprite::get_rendered_y() const {
    return get_rect()->y - Camera::get_instance()->get_y();
}