#include "Player.h"

#include "AssetManager.h"
#include "Food.h"
#include "System.h"
#include "GameEngine.h"

void Player::tick() {
    moveToMouse();
    handle_collision();
}

Player* Player::get_instance(){
    if (instance == nullptr) {
        instance = new Player("resources/images/circle.png", GameEngine::get_instance()->SCREEN_HEIGHT / 2,
                   GameEngine::get_instance()->SCREEN_WIDTH / 2, 15, 15);
    }

    return instance;
}

void Player::moveToMouse() {
    if (getCenterX() < mouse_x + 15 &&
        getCenterX() > mouse_x - 15 &&
        getCenterY() < mouse_y + 15 &&
        getCenterY() > mouse_y - 15) {
        return;
    }
    move_to_point(mouse_x, mouse_y);
        
    camera.x = (rect.x + rect.w / 2) - 640 / 2;
    camera.y = (rect.y + rect.h / 2) - 480 / 2;

    // Keep the camera in bounds
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > 3500 - camera.w) {
        camera.x = 3500 - camera.w;
    }
    if (camera.y > 3500 - camera.h) {
        camera.y = 3500 - camera.h;
    }
}

void Player::mouseMoved(double x, double y) {
    mouse_x = camera.x + camera.w / 2 - 640 / 2 + x;
    mouse_y = camera.y + camera.h / 2 - 480 / 2 + y;
}

Player* Player::instance;