#include "Player.h"
#include "Food.h"
#include "AssetManager.h"
#define PI 3.14

double Player::getDirToMouse() {
    double radian = std::atan2(mouse_y - getCenterY(), mouse_x - getCenterX());
    double angle = radian * (180 / PI);
    if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

void Player::tick() {
    moveToMouse();
    for (Sprite* s : AssetManager::get_instance()->sprites) {
        if (s == this) {
            continue;
        }
        if (Food* f = dynamic_cast<Food*>(s)) {
            if (SDL_HasIntersection(&rect, &s->rect)) {
                AssetManager::get_instance()->remove(*s);
                rect.w += f->rect.w;
                rect.h += f->rect.h;
            }
        }
    }
}

void Player::moveToMouse() {
    double dir = getDirToMouse();
    double x = std::cos(dir * (PI / 180));
    double y = std::sin(dir * (PI / 180));
    move(x * 5.0, y * 5.0);
}

void Player::mouseMoved(double x, double y) {
    mouse_x = x;
    mouse_y = y;
}