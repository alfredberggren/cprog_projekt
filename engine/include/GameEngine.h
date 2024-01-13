#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "LevelBackground.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "System.h"

typedef void (*funcPtr)();
typedef void (*funcPtr2)(Sprite*);

class GameEngine {
   private:
    std::vector<int> soundchannels_in_use;
    bool paused = false;
    bool key_quit = false;
    bool running = false;

    static GameEngine* instance;
    GameEngine(unsigned short fps, int screen_width, int screen_height, int level_width, int level_height);
    const unsigned short FRAMES_PER_SECOND;

    std::unordered_map<SDL_Keycode, funcPtr>* key_to_function_map;

    bool load_img(std::string path);
    bool load_sound(std::string path);

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;

   public:
    bool init_SDL_libraries();
    bool init_SDL_window(std::string windowTitle, int xPosition, int yPosition);

    void load_keys(std::unordered_map<SDL_Keycode, funcPtr> &keyMap);
    void use_function_on_all_sprites(funcPtr2);

    void run_game();
    void pause();
    void quit();
    void resume();

    static GameEngine* get_instance(unsigned short fps = 0, int screen_width = 0, int screen_height = 0, int level_width = 0, int level_height = 0);

    void load_assets(std::vector<std::string> assets);

    int play_sound(const std::string&, int, int) const;
    void stop_sound(int) const;

    void add_sprite(Sprite& sprite);
    
    void set_level_background(LevelBackground& bg);

    int get_sound_channel();
    void remove_used_channel(int channel);

    int get_screen_width() const;
    int get_screen_height() const;
    void set_screen_size(int, int);

    int get_level_height() const;
    int get_level_width() const;
    void set_level_size(int, int);

    ~GameEngine();
};


#endif  // GAME_ENGINE_H