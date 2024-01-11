#include "GlobuleGobbleSprite.h"

//CAMERA ZOOM
/* int GlobuleGobbleSprite::get_rendered_h() const {
    if (Camera::get_instance()->get_focused_on() == this) {
        return 100;  // bör vara variabel
    } else {
        return 100 +
               (getH() - Camera::get_instance()->get_focused_on()->getH());
    }
}

int GlobuleGobbleSprite::get_rendered_w() const {
    if (Camera::get_instance()->get_focused_on() == this) {
        return 100;  // bör vara variabel
    } else {
        return 100 +
               (getW() - Camera::get_instance()->get_focused_on()->getW());
    }
} */

int GlobuleGobbleSprite::get_rendered_x() const {
    return get_rect()->x - Camera::get_instance()->get_x();
}

int GlobuleGobbleSprite::get_rendered_y() const {
    return get_rect()->y - Camera::get_instance()->get_y();
}