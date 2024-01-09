#include "Character.h"
#include <vector>
#include "AssetManager.h"
#include "Food.h"

void Character::handle_collision() {
    std::vector<Sprite*> collisions =
        AssetManager::get_instance()->check_collisions(*this);
    if (collisions.empty()) {
        return;
    }
    for (Sprite* s : collisions) {
        if (Food* f = dynamic_cast<Food*>(s)) {
            this->expand();
            AssetManager::get_instance()->remove(*s);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand();
                AssetManager::get_instance()->remove(*s);
            } else {
                this->minimize();
                AssetManager::get_instance()->remove(*this);
            }
        }
    }
}

void Character::expand() {
    setW(getW() + 5);
    setH(getH() + 5);
}

void Character::minimize() {
    setW(getW() - 5);
    setH(getH() - 5);
}