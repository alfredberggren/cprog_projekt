#include <iostream>
#include <string>
#include "GameEngine.h"
#include <vector>

int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;
	

	SYSTEM.initSDLComponents();

	GameEngine* game = GameEngine::get_instance();

	std::vector<std::string> assets = {"resources/images/bg.jpg"};
	game->load_assets(assets);

	Sprite* s = new Sprite("resources/images/bg.jpg", 50,50,100,100);
	
	game->add_sprite(*s);
	

	game->run_game();
	
	return 0;
}