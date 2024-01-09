#include "Player.h"

#include "AssetManager.h"
#include "Food.h"
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
    std::vector<Sprite*> collided = AssetManager::get_instance()->check_collisions(*this);

    for (Sprite* sprite : collided){
        if (Food* f = dynamic_cast<Food*>(sprite)){
            expand();
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