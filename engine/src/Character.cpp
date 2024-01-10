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
            if (is_near_player())
                play_eat_food_sound();
            s->set_remove(true);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand((c->getW()*10)/getW(), (c->getH()*10)/getH());
                if (is_near_player())
                    play_eat_character_sound();
                c->set_remove(true);
            } else {
                set_remove(true);
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
    return BASE_SPEED + (200.0 / (rect.w / 2));
}

void Character::expand(int w, int h) {
    setW(getW() + w);
    setH(getH() + h);
}

void Character::minimize() {
    setW(getW() - 5);
    setH(getH() - 5);
}

bool Character::is_near_player(){
    int pX = Player::get_instance()->getCenterX();
    int pY = Player::get_instance()->getCenterY();
    
    if ((getCenterX() <  pX + 250) && (getCenterX() > pX - 250) && 
        (getCenterY() < pY + 250) && (getCenterY() > pY - 250)){
            return true;
    }
    return false;       
}

void Character::play_eat_character_sound(){
    GameEngine::get_instance()->play_sound("resources/sounds/munchbig.mp3", assigned_channel, 0);
}

/*Plays a eating food sound, "randomly" selected, based on Characters' rect:s x-position*/
void Character::play_eat_food_sound(){
    if (rect.x % 2 == 0) {
        GameEngine::get_instance()->play_sound("resources/sounds/munchsmall1.mp3", assigned_channel, 0);
    } else {
        GameEngine::get_instance()->play_sound("resources/sounds/munchsmall2.mp3", assigned_channel, 0);
    }
    
}