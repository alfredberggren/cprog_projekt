#include "NPC.h"

#include "AssetManager.h"

void NPC::tick() {
    move_to_closest();
    handle_collision();
}

void NPC::move_to_closest() {
    Sprite* closest = nullptr;
    double closest_dist = 1000000;
    for (Sprite* s : AssetManager::get_instance()->get_active_sprites()) {
        if (s == this) {
            continue;
        }
        double dist = std::sqrt(std::pow(getCenterX() - s->getCenterX(), 2) +
                                std::pow(getCenterY() - s->getCenterY(), 2));
        if (dist < closest_dist) {
            closest_dist = dist;
            closest = s;
        }
    }
    if (closest == nullptr) {
        return;
    }
    if (closest->area() > area()) {
        move_to_point(-closest->getCenterX(), -closest->getCenterY());
    } else {
        move_to_point(closest->getCenterX(), closest->getCenterY());
    }
}

void NPC::mouseMoved(double x, double y) {}