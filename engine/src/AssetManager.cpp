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

void AssetManager::handleKeyEvent(funcPtr2 func) {
    for (Sprite* sprite : active_sprites) {
        func(sprite);
    }
}

void AssetManager::add(Sprite& sprite) {
    active_sprites.push_back(&sprite);
}

void AssetManager::set_level_background(const LevelBackground& bg) {
    background = &bg;
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

void AssetManager::drawAll() const {
    if (background != nullptr){
        background->draw();
    }

    for (Sprite* sprite : active_sprites) {
        sprite->draw();
    }
}

/*function to be used by subclasses of Sprite to check if it has collided with
 * anything, will return a vector with all colliding sprites, which the subclass
 * can react to in its implementation*/
std::vector<Sprite*> AssetManager::check_collisions(const Sprite& sprite_to_check) const{
    std::vector<Sprite*> colliding_sprites;

    for (Sprite* sprite : active_sprites) {
        if (sprite->isCollidable()) {
            if (sprite != &sprite_to_check) {
                if (SDL_HasIntersection(sprite->get_rect(), sprite_to_check.get_rect()) ==
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
        if ((*it)->is_to_be_removed()) {
            delete *it;
            active_sprites.erase(it);
        } else if ((*it)->is_to_be_relocated()) {
            (*it)->setX(rand() % 3500);
            (*it)->setY(rand() % 3500);
            (*it)->set_relocate(false);
        }else {
            ++it;
        }
    }
}

void AssetManager::add_sound(const std::string path, Mix_Chunk* sound_chunk){
    loaded_sounds.insert(std::make_pair(path, sound_chunk));
}

void AssetManager::add_texture(const std::string path, SDL_Texture* texture){
    loaded_textures.insert(std::make_pair(path, texture));
}

Mix_Chunk* AssetManager::get_sound(const std::string path) const{
    return loaded_sounds[path];
}

SDL_Texture* AssetManager::get_texture(const std::string path) const {
    return loaded_textures[path];
}

std::unordered_map<std::string, SDL_Texture*> AssetManager::loaded_textures;
std::unordered_map<std::string, Mix_Chunk*> AssetManager::loaded_sounds;

AssetManager* AssetManager::instance;