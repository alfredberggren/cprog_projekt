#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"
#include "Player.h"
#include "Food.h"

using dir_iterator = std::filesystem::recursive_directory_iterator;

// Denna implementation get möjligheten att mappa en KEY till en specific funktion i en eller flera subklasser av Sprite. 
// Då är det helt upp till själva spelet / användaren att bestämma vad som ska utföras, alltså behövs det ingen funktion som
// downKeyPressed i Sprite vilket makear sense då inte alla spel använder downKey. 

// TODO: Ta reda på hur dyrt det är att kalla dynamic_cast i snabb intervall.
void expandPlayer(Sprite* s){
	if(Player* p = dynamic_cast<Player*>(s)){
		p->expand();
	}
}

void minimizePlayer(Sprite* s){
	if(Player* p = dynamic_cast<Player*>(s))
		p->minimize();
}

int main(int argc, char* argv[]) {
    std::string s1 = "Hejsan";
    std::cout << s1 << std::endl;

    SYSTEM.initSDLComponents();

    GameEngine* game = GameEngine::get_instance();

    std::vector<std::string> assets;

    for (const auto& dirEntry : dir_iterator("resources")) {
        if (dirEntry.is_regular_file())
            assets.push_back(dirEntry.path().generic_string());
    }

    game->load_assets(assets);

    Player* s = new Player("resources/images/circle.png", 320, 240, 100, 100);
    Food* f = new Food("resources/images/circle.png", 320, 240, 15, 15);
    Food* f2 = new Food("resources/images/circle.png", 600, 100, 15, 15);
    Food* f3 = new Food("resources/images/circle.png", 10, 270, 15, 15);
    Food* f4 = new Food("resources/images/circle.png", 460, 400, 15, 15);
    Food* f5 = new Food("resources/images/circle.png", 162, 67, 15, 15);
    Food* f6 = new Food("resources/images/circle.png", 267, 194, 15, 15);

    game->add_sprite(*s);
    game->add_sprite(*f);
    game->add_sprite(*f2);
    game->add_sprite(*f3);
    game->add_sprite(*f4);
    game->add_sprite(*f5);
    game->add_sprite(*f6);

    std::unordered_map<SDL_Keycode, funcPtr> map;
	map.emplace(SDLK_UP, expandPlayer);
	map.emplace(SDLK_DOWN, minimizePlayer);

	game->load_keys(map);

    game->run_game();

    return 0;
}