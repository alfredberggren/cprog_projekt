#include <iostream>
#include <string>
#include "GameEngine.h"
#include <vector>


int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;
	

	SYSTEM.initSDLComponents();

	GameEngine* game = GameEngine::get_instance();

	std::vector<std::string> assets = {"resources/images/bg.jpg", "resources/sounds/TillSpel.mp3"};
	game->load_assets(assets);

	Sprite* s = new Sprite("resources/images/bg.jpg", 50,50,100,100);
	Sprite* s2 = new Sprite("resources/images/bg.jpg", 150, 150, 50, 50);
	
	game->add_sprite(*s);
	game->add_sprite(*s2);
	

	game->run_game();
	
	return 0;
}