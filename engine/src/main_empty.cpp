#include <iostream>
#include <string>
#include "GameEngine.h"
#include <vector>
#include <filesystem>

using dir_iterator = std::filesystem::recursive_directory_iterator;

class Player : public Sprite {
	//TODO: singleton

	public:
		Player(std::string path, int x, int y, int w, int h) : Sprite(path, x, y, w, h) {}

		void tick(){
			
		}

		void mouseMoved(int x, int y){
			setX(x);
			setY(y);
		}
};

int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;
	
	SYSTEM.initSDLComponents();

	GameEngine* game = GameEngine::get_instance();

	std::vector<std::string> assets;

	for(const auto& dirEntry : dir_iterator("resources")){
		if(dirEntry.is_regular_file())
			assets.push_back(dirEntry.path().generic_string());
	}

	game->load_assets(assets);

	Player* s = new Player("resources/images/bg.jpg", 50,50,100,100);
	Player* s2 = new Player("resources/images/bg.jpg", 150, 150, 50, 50);
	
	game->add_sprite(*s);
	game->add_sprite(*s2);

	game->run_game();
	
	return 0;
}