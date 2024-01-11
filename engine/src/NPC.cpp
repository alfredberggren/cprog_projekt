#include "NPC.h"

#include "AssetManager.h"
#include "Food.h"



NPC::NPC(std::string path, int x, int y, int w, int h)
    : Character(path, x, y, w, h) {}

NPC* NPC::get_instance(std::string path, int x, int y, int w, int h) {
    return new NPC(path, x, y, w, h);
}

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
                constants::gResPath + "images/nervous.png");
            state = State::NERVOUS;
        }
        if (closest_dist < ESCAPE_BOOST_RADIUS) use_boost();
        move_in_dir(
            inv_dir(get_dir_to(closest->getCenterX(), closest->getCenterY())));
    } else {
        if (dynamic_cast<Food*>(closest)) {
            if (state != State::HUNGRY) {
                texture = AssetManager::get_instance()->get_texture(
                    constants::gResPath + "images/hungry.png");
                state = State::HUNGRY;
            }
        } else {
            if (state != State::ANGRY) {
                texture = AssetManager::get_instance()->get_texture(
                    constants::gResPath + "images/anger.png");
                state = State::ANGRY;
            }
            if (closest_dist < ATTACK_BOOST_RADIUS) use_boost();
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

void NPC::mouse_moved(double x, double y) {}

State NPC::get_state() const { return state; }