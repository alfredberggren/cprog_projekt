#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Map.h"
#include "Sprite.h"

typedef void (*funcPtr)();
typedef void (*funcPtr2)(Sprite *);

class AssetManager {
   private:
    static AssetManager *instance;
    Map *map = nullptr;

    std::vector<Sprite *> active_sprites;
    static std::unordered_map<std::string, SDL_Texture *> loaded_textures;
    static std::unordered_map<std::string, Mix_Chunk *> loaded_sounds;

    AssetManager();

   public:
    // TODO: why are these public? should do something about all of this...

    static AssetManager *get_instance();

    std::vector<Sprite *> check_collisions(const Sprite &) const;
    std::vector<Sprite *> get_active_sprites() const { return active_sprites; }
    void handle_key_event(funcPtr2 func);
    void add(Sprite &);
    void tick_all();
    void mouse_moved_all(double, double);
    void remove_marked();

    void add_sound(const std::string, Mix_Chunk *);
    void add_texture(const std::string, SDL_Texture *);
    Mix_Chunk *get_sound(const std::string);
    SDL_Texture *get_texture(const std::string);

    void draw_all();
    void set_map(Map &);

    // Sets camera to follow largest character
    void camera_follow_largest() const;

    ~AssetManager();
};

#endif  // ASSET_MANAGER_H