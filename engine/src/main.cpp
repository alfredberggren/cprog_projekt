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

    Player* s = new Player("resources/images/circle.png", 320, 240, 100, 100);
    Food* f = new Food("resources/images/circle.png", 100, 100, 15, 15);
    Food* f2 = new Food("resources/images/circle.png", 600, 100, 15, 15);
    Food* f3 = new Food("resources/images/circle.png", 10, 270, 15, 15);
    Food* f4 = new Food("resources/images/circle.png", 460, 400, 15, 15);
    Food* f5 = new Food("resources/images/circle.png", 162, 67, 15, 15);
    Food* f6 = new Food("resources/images/circle.png", 267, 194, 15, 15);
    NPC* n = new NPC("resources/images/circle.png", 0, 0, 20, 20);
    NPC* n2 = new NPC("resources/images/circle.png", 600, 400, 20, 20);


    game->add_sprite(*s);
    game->add_sprite(*f);

    Map* b = new Map("resources/images/bg.jpg", 0, 0, 1920, 1280);

    game->add_sprite(*b);
    /*game->add_sprite(*f2);
    game->add_sprite(*f2);
    game->add_sprite(*f3);
    game->add_sprite(*f4);
    game->add_sprite(*f5);
    game->add_sprite(*f6);
    game->add_sprite(*n);
    game->add_sprite(*n2);*/

    map.emplace(SDLK_UP, expandPlayer);
    map.emplace(SDLK_DOWN, minimizePlayer);

    game->load_keys(map);

    game->run_game();

    return 0;
}