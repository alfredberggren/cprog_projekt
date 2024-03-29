#include "AssetManager.h"

AssetManager::AssetManager() {
    
}

AssetManager* AssetManager::get_instance() {
    if (instance == nullptr) {
        instance = new AssetManager();
        std::cout << "AssetManager:\n\t- Created AssetManager" << std::endl;
    }
    return instance;
}

AssetManager::~AssetManager() {
    std::cout << "AssetManager:" << std::endl;

    for (Sprite* s : sprites_to_be_added_in_game_loop){
        delete s;
        std::cout << "\t- Deleted sprite from 'sprite_to_be_added...'" << std::endl;
    }

    for (Sprite* s : active_sprites){
        delete s;
         std::cout << "\t- Deleted sprite from 'active_sprites'" << std::endl;

    }
    
    for (auto pair : loaded_textures) {
        SDL_DestroyTexture(pair.second);
        std::cout << "\t- Destroyed Texture: " << pair.first << std::endl;
    }
    for (auto pair : loaded_sounds) {
        Mix_FreeChunk(pair.second);
        std::cout << "\t- Freed Chunk: " << pair.first << std::endl;
    }
    std::cout << "\t--- AssetManager Destroyed ---" << std::endl;
}

void AssetManager::handle_key_event(funcPtr2 func) {
    for (Sprite* sprite : active_sprites) {
        func(sprite);
    }
}

void AssetManager::add(Sprite& sprite) {
    active_sprites.push_back(&sprite);
}

void AssetManager::add_while_running(Sprite& sprite){
    sprites_to_be_added_in_game_loop.push_back(&sprite);
}

void AssetManager::add_new_sprites_to_game() {
    for (Sprite* s : sprites_to_be_added_in_game_loop){
        active_sprites.push_back(s);
    }
    sprites_to_be_added_in_game_loop.clear();
}

void AssetManager::set_level_background(const LevelBackground& bg) {
    background = &bg;
}

void AssetManager::tick_all() {
    for (Sprite* sprite : active_sprites) {
        sprite->tick();
    }
}

void AssetManager::mouse_moved_all(double x, double y) {
    for (Sprite* sprite : active_sprites) {
        sprite->mouse_moved(x, y);
    }
}

void AssetManager::draw_all() const {
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
std::vector<Sprite*> AssetManager::check_collisions(
    const Sprite& sprite_to_check) const {
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

// Will remove active sprites that has been marked for removal. 
void AssetManager::remove_marked() {
    std::vector<Sprite*>::iterator it;
    for (it = active_sprites.begin(); it != active_sprites.end();) {
        if ((*it)->is_to_be_removed()) {
            delete *it;
            active_sprites.erase(it);
        } else {
            ++it;
        }
    }
}

void AssetManager::add_sound(const std::string path, Mix_Chunk* sound_chunk) {
    loaded_sounds.insert(std::make_pair(path, sound_chunk));
    std::cout << "AssetManager:\n\t- Added sound: " << path << std::endl;
}

void AssetManager::add_texture(const std::string path, SDL_Texture* texture) {
    loaded_textures.insert(std::make_pair(path, texture));
    std::cout << "AssetManager:\n\t- Added texture: " << path << std::endl;
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