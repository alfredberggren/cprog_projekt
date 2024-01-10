#include "NPC.h"

#include "AssetManager.h"
#include "Food.h"

void NPC::tick() { Character::tick(); }

void NPC::char_move() {
    Sprite* closest = nullptr;
    double closest_dist = 1000000;
    for (Sprite* s : AssetManager::get_instance()->get_active_sprites()) {
        if (s == this) {
            continue;
        }
        double dist = std::sqrt(std::pow(getCenterX() - s->getCenterX(), 2) +
                                std::pow(getCenterY() - s->getCenterY(), 2));
        if (dynamic_cast<Food*>(s)) {
            if (dist > FOG_RADIUS) {
                continue;
            }
        }
        if (dist < closest_dist) {
            closest_dist = dist;
            closest = s;
        }
    }
    if (closest == nullptr) {
        return;
    }
    if (closest->area() >= area()) {
        if (state != State::NERVOUS) {
            texture = AssetManager::get_instance()->get_texture(
                "resources/images/nervous.png");
            state = State::NERVOUS;
        }
        if (closest_dist < 100) use_boost();
        move_in_dir(
            inv_dir(get_dir_to(closest->getCenterX(), closest->getCenterY())));
    } else {
        if (dynamic_cast<Food*>(closest)) {
            if (state != State::HUNGRY) {
                texture = AssetManager::get_instance()->get_texture(
                    "resources/images/hungry.png");
                state = State::HUNGRY;
            }
        } else {
            if (state != State::ANGRY) {
                texture = AssetManager::get_instance()->get_texture(
                    "resources/images/anger.png");
                state = State::ANGRY;
            }
            if (closest_dist < 500) use_boost();
        }
        move_in_dir(get_dir_to(closest->getCenterX(), closest->getCenterY()));
    }
}

double NPC::inv_dir(double dir) {
    dir += 180;
    if (dir > 360) {
        dir -= 360;
    }
    return dir;
}

void NPC::mouseMoved(double x, double y) {}