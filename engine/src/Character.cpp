#include "Character.h"
#include <vector>
#include "AssetManager.h"
#include "Food.h"
#include "GameEngine.h"

void Character::handle_collision() {
    std::vector<Sprite*> collisions =
        AssetManager::get_instance()->check_collisions(*this);
    if (collisions.empty()) {
        return;
    }
    for (Sprite* s : collisions) {
        if (dynamic_cast<Food*>(s)) {
            this->expand(s->getW(), s->getH());
            GameEngine::get_instance()->play_sound("resources/sounds/munchsmall1.mp3", 0);
            s->set_remove(true);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand(c->getW(), c->getH());
                GameEngine::get_instance()->play_sound("resources/sounds/munchbig.mp3", 0);
                c->set_remove(true);
            } else {
                this->minimize();
                set_remove(true);
            }
        }
    }
}

void Character::expand(int w, int h) {
    setW(getW() + w);
    setH(getH() + h);
}

void Character::minimize() {
    setW(getW() - 5);
    setH(getH() - 5);
}