#include "AssetManager.h"

AssetManager::AssetManager() {
    // Constructor implementation
    // Initialize the sprite vector
}

AssetManager::~AssetManager() {
    std::cout << "Destroying AssetManager" << std::endl;
    for (auto pair : loaded_textures) {
        SDL_DestroyTexture(pair.second);
    }
    for (auto pair : loaded_sounds) {
        Mix_FreeChunk(pair.second);
    }
}

void AssetManager::handleKeyEvent(funcPtr func) {
    for (Sprite* sprite : active_sprites) {
        func(sprite);
    }
}

void AssetManager::add(Sprite& sprite) {
    active_sprites.push_back(&sprite);
    std::cout << "Added a sprite to active_sprites, total now: "
              << active_sprites.size() << std::endl;
}

void AssetManager::tickAll() {
    for (Sprite* sprite : active_sprites) {
        sprite->tick();
    }
}

void AssetManager::mouseMovedAll(double x, double y) {
    for (Sprite* sprite : active_sprites) {
        sprite->mouseMoved(x, y);
    }
}

void AssetManager::drawAll() {
    for (Sprite* sprite : active_sprites) {
        sprite->draw();
    }
}

/*function to be used by subclasses of Sprite to check if it has collided with
 * anything, will return a vector with all colliding sprites, which the subclass
 * can react to in its implementation*/
std::vector<Sprite*> AssetManager::check_collisions(Sprite& sprite_to_check) {
    std::vector<Sprite*> colliding_sprites;

    for (Sprite* sprite : active_sprites) {
        if (sprite->isCollidable()) {
            if (sprite != &sprite_to_check) {
                if (SDL_HasIntersection(&sprite->rect, &sprite_to_check.rect) ==
                    SDL_TRUE) {
                    colliding_sprites.push_back(sprite);
                }
            }
        }
    }

    return colliding_sprites;
}  // check_collisions

void AssetManager::remove_marked() {
    std::vector<Sprite*>::iterator it;
    for (it = active_sprites.begin(); it != active_sprites.end();) {
        if ((*it)->to_remove()) {
            std::cout << "removing sprite" << std::endl;
            delete *it;
            active_sprites.erase(it);
        } else {
            ++it;
        }
    }
}

std::unordered_map<std::string, SDL_Texture*> AssetManager::loaded_textures;
std::unordered_map<std::string, Mix_Chunk*> AssetManager::loaded_sounds;

AssetManager* AssetManager::instance;