#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Food.h"
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "NPC.h"

using dir_iterator = std::filesystem::recursive_directory_iterator;

// Denna implementation get möjligheten att mappa en KEY till en specific
// funktion i en eller flera subklasser av Sprite. Även funktioner i Sprite går
// bra. Då är det helt upp till själva spelet / användaren att bestämma vad som
// ska utföras, alltså behövs det ingen funktion som som hanterar tryck av
// tangenten 'J' i Sprite t.ex.

// TODO: Ta reda på hur dyrt det är att kalla dynamic_cast i snabb intervall.
void expandPlayer(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) {
        p->expand(5, 5);
    }
}

void minimizePlayer(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) p->minimize();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> assets;
    std::unordered_map<SDL_Keycode, funcPtr> map;
    GameEngine* game = GameEngine::get_instance();

    game->init_SDL_libraries();
    game->init_SDL_window("NOT AGARIO COPY", SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED, 640, 480);

    for (const auto& dirEntry : dir_iterator("resources")) {
        if (dirEntry.is_regular_file())
            assets.push_back(dirEntry.path().generic_string());
    }

    game->load_assets(assets);

    int soundchannel = game->play_sound("resources/sounds/TillSpel.mp3", -1);
    

    int LEVEL_WIDTH = 5000;
    int LEVEL_HEIGHT = 5000;

    Player* s = new Player("resources/images/circle.png", game->SCREEN_HEIGHT / 2, game->SCREEN_WIDTH / 2, 15, 15);
    // make food and npcs randomly placed within level width and height
    for (int i = 0; i < 100; i++)
    {
        game->add_sprite(*new Food("resources/images/circle.png", rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT, 15, 15));
    }
    //for (int i = 0; i < 15; i++)
    //{
       // game->add_sprite(*new NPC("resources/images/circle.png", rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT, 20, 20));
    //}

    game->add_sprite(*s);

    //Map* b = new Map("resources/images/bg.jpg", 0, 0, 1920, 1280);
    //game->add_sprite(*b);

    map.emplace(SDLK_UP, expandPlayer);
    map.emplace(SDLK_DOWN, minimizePlayer);

    game->load_keys(map);

    game->run_game();

    return 0;
}