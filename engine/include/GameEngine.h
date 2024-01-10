#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AssetManager.h"
#include "Sprite.h"
#include "System.h"
#include "Map.h"

typedef void (*funcPtr)();
typedef void (*funcPtr2)(Sprite*);

class GameEngine {
   private:
    std::vector<int> soundchannels_in_use;
    bool paused = false;

    static GameEngine* instance;
    GameEngine(/* args */);

    std::unordered_map<SDL_Keycode, funcPtr>* keyMapping;

    bool load_img(std::string path);
    bool load_sound(std::string path);

   public:

    // Istället för att ha SYSTEM variabeln i main kan vi låta kommunikationen mellan faktiska spelet/användaren och System utföras av GameEngine.
    // Nedan är 2 funktioner som exemplifierar detta.  
    // ** Fundering ** Ge möjligheten att välja vilka SDL bibliotek man vill inkludera till sin GameEngine? 
    bool init_SDL_libraries();
    bool init_SDL_window(std::string windowTitle, int xPosition, int yPosition,
                       int width, int height);

    void load_keys(std::unordered_map<SDL_Keycode, funcPtr> &map);
    void add_key_function_for_sprite(funcPtr2);

    void run_game();

    static GameEngine* get_instance();

    void load_assets(std::vector<std::string> assets);
    void loadSurface(std::string& asset, SDL_Surface* surface, int& retFlag);
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    void pause();

    int play_sound(const std::string&, int, int) const;
    void stop_sound(int) const;

    void add_sprite(Sprite& sprite);
    void set_map(Map& map);

    int get_sound_channel();
    void remove_used_channel(int channel);

    ~GameEngine();
};

#endif  // GAME_ENGINE_H