/*TODO:
-- Spelmotor --
    X. Kolla ljudkanaler, vad är smartast att göra? 
        - Implementerade någon sorts "hålla koll på vilka kanaler som används"-funktionalitet i gameengine. Vet inte hur smart det är egentligen.
    2. Hur ska man kunna lägga till bakgrund?
    3. Hantera FPS
    4. Dynamisk allokering, se till att saker o ting inte har publika konstruktorer om de inte ska ha det osv (Sprite t.ex.)
    5. Möjlighet att starta, pausa, avsluta spel. GameEngine borde alltså ha:
        - start_game(), 
        - pause_game(), 
        - resume_game(), 
        - stop_game() (spelet avslutas, men programmet körs) och 
        - close_game() (avslutar allt)... 
        - (RestartGame??))
    6. Implementera sätt att avgöra när ett spel är slut? Eller är det för spelspecifikt,?
    7. Implementera något sätt att lägga in något som ska hända varje spel-tick, t.ex. att lägga till mer mat? 
    8. PixelPerfectCollisionDetection!!!!
    9. Hur kan den som implementerar välja att använda Camera-grejen eller inte?
    

-- Spelet --
    1. "Dumma ner" NPCs, mer random, inte märker spelaren/att man är större, delay på handlingar
    2. Se till att NPCs inte kan gå utanför kartan
    3. Tweaka hastigheter
    4. Randomisera  vilka ljud som spelas när man äter (finns två i nuläget)
    5. "Zooma ut" kameran när spelare blivit för stor.
    6. Sätt spelaren i mitten av kartan vid spelstart


*/


#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Food.h"
#include "GameEngine.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"

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

void use_player_boost(Sprite* s){
    if(Player* p = dynamic_cast<Player*>(s))
        p->boost_pressed();

}




/*
void example(){
    GameEngine::get_instance()->do_on_all_sprites(use_player_boost);
}

map.emplace(SDLK_UP, example);
*/

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

    

    int LEVEL_WIDTH = 3500;
    int LEVEL_HEIGHT = 3500;

    Map* m = Map::get_instance("resources/images/spaceBackground.jpg", LEVEL_WIDTH, LEVEL_HEIGHT);
    game->set_map(*m);

    Player* s =
        Player::get_instance();
    
    // make food and npcs randomly placed within level width and height
    for (int i = 0; i < 600; i++)
    {
        game->add_sprite(*new Food("resources/images/circle.png", rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT, 15, 15));
    }
    
    for (int i = 0; i < 30; i++)
    {
       game->add_sprite(*new NPC("resources/images/circle.png", rand() % LEVEL_WIDTH, rand() % LEVEL_HEIGHT, 20, 20));
    }

    game->add_sprite(*s);

    map.emplace(SDLK_UP, expandPlayer);
    map.emplace(SDLK_DOWN, minimizePlayer);
    map.emplace(SDLK_SPACE, use_player_boost);

    game->load_keys(map);
    
    game->play_sound("resources/sounds/TillSpel.mp3", GameEngine::get_instance()->get_sound_channel(), -1);
    game->run_game();

    return 0;
}