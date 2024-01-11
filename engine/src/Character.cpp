#include "Character.h"

#include <vector>

#include "AssetManager.h"
#include "Camera.h"
#include "Food.h"
#include "GameEngine.h"
#define BASE_SPEED 30.0
#define FIRST_LOCAL_SOUNDCHANNEL 0
#define TOTAL_LOCAL_SOUNDCHANNELS 4

Character::Character(std::string path, int x, int y, int w, int h)
    : GlobuleGobbleSprite(path, x, y, w, h, true),
      boost_counter(0),
      boost_timer(0),
      boost_speed(0),
      current_local_soundchannel(FIRST_LOCAL_SOUNDCHANNEL) {
    for (int i = FIRST_LOCAL_SOUNDCHANNEL; i < TOTAL_LOCAL_SOUNDCHANNELS; ++i) {
        local_soundchannels.push_back(
            GameEngine::get_instance()->get_sound_channel());
    }
}

Character::~Character() {
    for (int i = FIRST_LOCAL_SOUNDCHANNEL; i < TOTAL_LOCAL_SOUNDCHANNELS; ++i) {
        GameEngine::get_instance()->remove_used_channel(local_soundchannels[i]);
    }
}

void Character::tick() {
    check_boost();
    char_move();
    if (this == Camera::get_instance()->get_focused_on()) {
        Camera::get_instance()->center();
    }
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
            this->expand(f);
            if (is_near_player()) play_eat_food_sound();
            f->kill(*this);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand(c);
                if (is_near_player()) play_eat_character_sound();
                c->kill(*this);
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
    return BASE_SPEED * pow(area(), -0.230) + boost_speed;
    // return BASE_SPEED + (200.0 / (rect.w / 2) + boost_speed);
}

void Character::expand(Sprite* eaten_sprite) {
    boost_counter++;
    int expand_w = (eaten_sprite->getW() * EXPAND_AMOUNT) / getW();
    int expand_h = (eaten_sprite->getH() * EXPAND_AMOUNT) / getH();
    setW(getW() + expand_w);
    setH(getH() + expand_h);
    if (Camera::get_instance()->get_focused_on() == this) {
        Camera::get_instance()->center();
    }
}

void Character::minimize() {
    setW(getW() - MINIMIZE_AMOUNT);
    setH(getH() - MINIMIZE_AMOUNT);
}

void Character::set_boost_speed(int speed) { boost_speed = speed; }

bool Character::has_boost() const { return (boost_counter >= MAX_BOOST); }

void Character::check_boost() {
    if (boost_timer > 0) {
        set_boost_speed(BOOST_SPEED);
        --boost_timer;
    } else
        set_boost_speed(0);
}

void Character::use_boost() {
    if (has_boost()) {
        if (this == Player::get_instance()) {
            GameEngine::get_instance()->play_sound(
                "resources/sounds/BoosterActivated.mp3",
                get_local_soundchannel(), 0);
        } else if (is_near_player()) {
            GameEngine::get_instance()->play_sound(
                "resources/sounds/JustBoost.mp3", get_local_soundchannel(), 0);
        }
        boost_timer = BOOST_LENGTH;
        boost_counter = 0;
    }
}

bool Character::is_near_player() const {
    int pX = Player::get_instance()->getCenterX();
    int pY = Player::get_instance()->getCenterY();

    if ((getCenterX() < pX + NEAR_PLAYER_RADIUS) &&
        (getCenterX() > pX - NEAR_PLAYER_RADIUS) &&
        (getCenterY() < pY + NEAR_PLAYER_RADIUS) &&
        (getCenterY() > pY - NEAR_PLAYER_RADIUS)) {
        return true;
    }
    return false;
}

int Character::get_local_soundchannel() {
    if (++current_local_soundchannel == TOTAL_LOCAL_SOUNDCHANNELS) {
        current_local_soundchannel = FIRST_LOCAL_SOUNDCHANNEL;
    }
    return local_soundchannels[current_local_soundchannel];
}

void Character::play_eat_character_sound() {
    GameEngine::get_instance()->play_sound("resources/sounds/munchbig.mp3",
                                           get_local_soundchannel(), 0);
}

/*Plays a eating food sound, "randomly" selected, based on Characters' rect:s
 * x-position*/
void Character::play_eat_food_sound() {
    if (Sprite::get_rect()->x % 2 == 0) {
        GameEngine::get_instance()->play_sound(
            "resources/sounds/munchsmall1.mp3", get_local_soundchannel(), 0);
    } else {
        GameEngine::get_instance()->play_sound(
            "resources/sounds/munchsmall2.mp3", get_local_soundchannel(), 0);
    }

    if (boost_counter == MAX_BOOST) {
        if (this == Player::get_instance()) {
            GameEngine::get_instance()->play_sound(
                "resources/sounds/BoosterReady.mp3", get_local_soundchannel(),
                0);
        }
    }
}

void Character::kill(Sprite& killed_by) {
    set_remove(true);
    if (Camera::get_instance()->get_focused_on() == this) {
        Camera::get_instance()->set_focused_on(killed_by);
    }
}

