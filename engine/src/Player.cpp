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
    handle_collision();
}

void Player::moveToMouse() {
    if (getCenterX() < mouse_x + 15 && getCenterX() > mouse_x - 15 &&
        getCenterY() < mouse_y + 15 && getCenterY() > mouse_y - 15) {
        return;
    }
    double dir = getDirToMouse();
    double x = std::cos(dir * (PI / 180));
    double y = std::sin(dir * (PI / 180));
    move(x * 15.0, y * 15.0);
}

void Player::mouseMoved(double x, double y) {
    mouse_x = x;
    mouse_y = y;
}