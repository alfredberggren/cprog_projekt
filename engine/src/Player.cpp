#include "Player.h"

#include "AssetManager.h"
#include "Food.h"
#include "System.h"

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
    std::cout << getCenterX() << " " << getCenterY() << std::endl;
        
    camera.x = (rect.x + rect.w / 2) - 640 / 2;
    camera.y = (rect.y + rect.h / 2) - 480 / 2;
}

void Player::mouseMoved(double x, double y) {
    mouse_x = x;
    mouse_y = y;
}