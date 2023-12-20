//
//  c++_empty
//  

#include <iostream>
#include <string>
#include "GameEngine.h"

int main(int argc, char* argv[]) {
	std::string s1 = "Hejsan";
	std::cout << s1 << std::endl;

	GameEngine* game = GameEngine::get_instance();

	game->run_game();
	
	return 0;
}