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

		void expand(){
			
		}

		void minimize(){
			
		}

		void mouseMoved(double x, double y){
			setX(x);
			setY(y);
		}
};

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

	for(const auto& dirEntry : dir_iterator("resources")){
		if(dirEntry.is_regular_file())
			assets.push_back(dirEntry.path().generic_string());
	}

	game->load_assets(assets);

	Player* s = new Player("resources/images/bg.jpg", 50,50,100,100);
	Player* s2 = new Player("resources/images/bg.jpg", 150, 150, 50, 50);
	
	game->add_sprite(*s);
	game->add_sprite(*s2);

	std::unordered_map<SDL_Keycode, funcPtr> map;
	map.emplace(SDLK_UP, expandPlayer);
	map.emplace(SDLK_DOWN, minimizePlayer);

	game->load_keys(map);

	game->run_game();
	
	return 0;
}