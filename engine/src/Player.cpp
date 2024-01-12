#include "Player.h"

#include "AssetManager.h"
#include "Food.h"
#include "GameEngine.h"
#include "System.h"

Player::Player(std::string path, int x, int y, int w, int h)
    : Character(path, x, y, w, h) {}

void Player::tick() { Character::tick(); }

Player* Player::get_instance() {
    if (instance == nullptr) {
        instance = new Player(
            constants::gResPath + "images/alien2.png",
            GameEngine::get_instance()->get_screen_height() / 2,
            GameEngine::get_instance()->get_screen_width() / 2, 21, 21);
    }
    return instance;
}

// Flyttar spelaren mot muspekaren
void Player::char_move() {
    // Om muspekaren är inom 15 pixlar från karaktären, gör ingenting
    if (dir_to_mouse == -1) {
        return;
    }
    move_in_dir(dir_to_mouse);
}

void Player::mouse_moved(double x, double y) {
    mouse_x = Camera::get_instance()->get_x() + Camera::get_instance()->get_w() / 2 - GameEngine::get_instance()->get_screen_width() / 2 + x;
    mouse_y = Camera::get_instance()->get_y() + Camera::get_instance()->get_h() / 2 - GameEngine::get_instance()->get_screen_height() / 2 + y;

    if (getCenterX() < mouse_x + 15 && getCenterX() > mouse_x - 15 &&
        getCenterY() < mouse_y + 15 && getCenterY() > mouse_y - 15) {
        dir_to_mouse = -1;
        return;
    }
    dir_to_mouse = get_dir_to(mouse_x, mouse_y);
}

void Player::boost_pressed() { use_boost(); }

Player* Player::instance;
