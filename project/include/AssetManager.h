#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Sprite.h"
#include "LevelBackground.h"

typedef void (*funcPtr)();
typedef void (*funcPtr2)(Sprite *);

class AssetManager {
   private:
    static AssetManager *instance;
    const LevelBackground* background = nullptr;
    std::vector<Sprite *> sprites_to_be_added_in_game_loop;
    std::vector<Sprite *> active_sprites;
    static std::unordered_map<std::string, SDL_Texture *> loaded_textures;
    static std::unordered_map<std::string, Mix_Chunk *> loaded_sounds;

    AssetManager();

public:
    static AssetManager *get_instance();

    std::vector<Sprite *> check_collisions(const Sprite &) const;
    const std::vector<Sprite *> get_active_sprites() const { return active_sprites; }
    void handle_key_event(funcPtr2 func);
    void add(Sprite &);
    void add_while_running(Sprite &);
    void add_new_sprites_to_game();
    void tick_all();
    void mouse_moved_all(double, double);
    void remove_marked();

    void add_sound(const std::string, Mix_Chunk*);
    void add_texture(const std::string, SDL_Texture*);
    Mix_Chunk* get_sound(const std::string) const;
    SDL_Texture* get_texture(const std::string) const;
    

    void draw_all() const;
    void set_level_background(const LevelBackground&);

    ~AssetManager();
};

#endif  // ASSET_MANAGER_H