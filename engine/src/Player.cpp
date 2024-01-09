#include "Player.h"

#include "AssetManager.h"
#include "Food.h"

/*double Player::getDirToMouse() {
    double radian = std::atan2(mouse_y - getCenterY(), mouse_x - getCenterX());
    double angle = radian * (180 / PI);
    if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}*/

void Player::tick() {
    moveToMouse();
    handle_collision();
}

void Player::moveToMouse() {
    if (getCenterX() < mouse_x + 15 && getCenterX() > mouse_x - 15 &&
        getCenterY() < mouse_y + 15 && getCenterY() > mouse_y - 15) {
        return;
    }
    move_to_point(mouse_x, mouse_y);
}

void Player::mouseMoved(double x, double y) {
    mouse_x = x;
    mouse_y = y;
}