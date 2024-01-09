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
        if (dynamic_cast<Food*>(s)) {
            this->expand(s->getW(), s->getH());
            s->set_remove(true);
        } else if (Character* c = dynamic_cast<Character*>(s)) {
            if (area() > c->area()) {
                this->expand(c->getW(), c->getH());
                c->set_remove(true);
            } else {
                this->minimize();
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
    move(x1 * 5.0, y1 * 5.0);
}

void Character::expand(int w, int h) {
    setW(getW() + w);
    setH(getH() + h);
}

void Character::minimize() {
    setW(getW() - 5);
    setH(getH() - 5);
}