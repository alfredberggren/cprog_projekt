#include "Character.h"

#include <vector>

#include "AssetManager.h"
#include "Food.h"
#include "GameEngine.h"
#define BASE_SPEED 1.0

void Character::handle_collision() {
    std::vector<Sprite*> collisions =
        AssetManager::get_instance()->check_collisions(*this);
    if (collisions.empty()) {
        return;
    }
    for (Sprite* s : collisions) {
        if (Food* f = dynamic_cast<Food*>(s)) {
            this->expand((f->getW()*10)/getW(), (f->getH()*10)/getH());
            GameEngine::get_instance()->play_sound("resources/sounds/munchsmall1.mp3", assigned_channel, 0);
            s->set_remove(true);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand((c->getW()*10)/getW(), (c->getH()*10)/getH());
                GameEngine::get_instance()->play_sound("resources/sounds/munchbig.mp3", assigned_channel, 0);
                c->set_remove(true);
            } else {
                set_remove(true);
            }
        }
    }
}

void Character::move_to_point(double x, double y) {
    double radian = std::atan2(y - getCenterY(), x - getCenterX());
    double angle = radian * (180 / PI);
    if (angle < 0.0) {
        angle += 360.0;
    }
    double x1 = std::cos(angle * (PI / 180));
    double y1 = std::sin(angle * (PI / 180));
    move(x1 * get_vel(), y1 * get_vel());
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

void Character::set_boost_speed(int speed){
    boost_speed = speed;
}

bool Character::has_boost() const{
    return boost_counter >= 20;
}

void Character::check_boost(){
    if(boost_timer > 0){
        set_boost_speed(20);
        --boost_timer;
    }
    else
        set_boost_speed(0);
}

void Character::use_boost(){
    if(has_boost()){
        boost_timer = 50;
        boost_counter = 0;
    }
}


