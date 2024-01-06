#include <iostream>
#include <string>
#include "GameEngine.h"
#include <vector>
#include <filesystem>

using dir_iterator = std::filesystem::recursive_directory_iterator;


int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;
	

	
	SYSTEM.initSDLComponents();

	GameEngine* game = GameEngine::get_instance();

	std::vector<std::string> assets;
	game->load_assets(assets);

	for(const auto& dirEntry : dir_iterator("resources")){
		if(dirEntry.is_regular_file())
			assets.push_back(dirEntry.path().generic_string());
	}

	game->load_assets(assets);

	Sprite* s = new Sprite("resources/images/bg.jpg", 50,50,100,100);
	Sprite* s2 = new Sprite("resources/images/bg.jpg", 150, 150, 50, 50);
	
	game->add_sprite(*s);
	game->add_sprite(*s2);

	game->run_game();
	
	return 0;
}