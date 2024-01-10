#include "Character.h"

#include <vector>

#include "AssetManager.h"
#include "Food.h"
#include "GameEngine.h"
#define BASE_SPEED 1.0

void Character::tick() {
    check_boost();
    char_move();
    if(followed_by_camera) center_camera();
    handle_collision();
}

void Character::handle_collision() {
    std::vector<Sprite*> collisions =
        AssetManager::get_instance()->check_collisions(*this);
    if (collisions.empty()) {
        return;
    }
    for (Sprite* s : collisions) {
        if (Food* f = dynamic_cast<Food*>(s)) {
            this->expand((f->getW() * 10) / getW(), (f->getH() * 10) / getH());
            if (is_near_player()) play_eat_food_sound();
            s->kill(this);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand((c->getW() * 10) / getW(),
                             (c->getH() * 10) / getH());
                if (is_near_player()) play_eat_character_sound();
                c->kill(this);
            }
        }
    }
}

// Flyttar character i den givna riktningen
void Character::move_in_dir(double dir) {
    double x1 = std::cos(dir * (PI / 180));
    double y1 = std::sin(dir * (PI / 180));
    move(x1 * get_vel(), y1 * get_vel());
}

// Returnerar vinkeln mellan character och punkten (x, y)
double Character::get_dir_to(double x, double y) {
    double radian = std::atan2(y - getCenterY(), x - getCenterX());
    double angle = radian * (180 / PI);
    if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

double Character::get_vel() const {
    return BASE_SPEED + (200.0 / (rect.w / 2) + boost_speed);
}

void Character::expand(int w, int h) {
    boost_counter++;
    setW(getW() + w);
    setH(getH() + h);
}

void Character::minimize() {
    setW(getW() - 5);
    setH(getH() - 5);
}

void Character::set_boost_speed(int speed) { boost_speed = speed; }

bool Character::has_boost() const { return boost_counter >= 10; }

void Character::check_boost() {
    if (boost_timer > 0) {
        set_boost_speed(10);
        --boost_timer;
    } else
        set_boost_speed(0);
}

void Character::use_boost() {
    if (has_boost()) {
        boost_timer = 25;
        boost_counter = 0;
    }
}

bool Character::is_near_player() {
    int pX = Player::get_instance()->getCenterX();
    int pY = Player::get_instance()->getCenterY();

    if ((getCenterX() < pX + 250) && (getCenterX() > pX - 250) &&
        (getCenterY() < pY + 250) && (getCenterY() > pY - 250)) {
        return true;
    }
    return false;
}

void Character::play_eat_character_sound() {
    GameEngine::get_instance()->play_sound("resources/sounds/munchbig.mp3",
                                           assigned_channel, 0);
}

/*Plays a eating food sound, "randomly" selected, based on Characters' rect:s
 * x-position*/
void Character::play_eat_food_sound() {
    if (rect.x % 2 == 0) {
        GameEngine::get_instance()->play_sound(
            "resources/sounds/munchsmall1.mp3", assigned_channel, 0);
    } else {
        GameEngine::get_instance()->play_sound(
            "resources/sounds/munchsmall2.mp3", assigned_channel, 0);
    }
}

void Character::center_camera() {
    camera.x = (rect.x + rect.w / 2) - 640 / 2;
    camera.y = (rect.y + rect.h / 2) - 480 / 2;

    // Håll kameran inom spelplanen
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

void Character::kill(Sprite* killed_by) {
    set_remove(true);
    if (followed_by_camera) {
        if (killed_by != nullptr) {
            killed_by->set_followed_by_camera(true);
        }
        set_followed_by_camera(false);
    }
}