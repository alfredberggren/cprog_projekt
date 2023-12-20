//
//  c++_empty
//  

#include <iostream>
#include <string>
#include "GameEngine.h"
#include <vector>

int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;

	GameEngine* game = GameEngine::get_instance();

	std::vector<std::string> assets = {"resources/images/bg.jpg"};

	game->load_assets(assets);

	game->run_game();
	
	return 0;
}