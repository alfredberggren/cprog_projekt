/*TODO:
-- Spelmotor --
    4. Dynamisk allokering, se till att saker o ting inte har publika konstruktorer om de inte ska ha det osv (Sprite t.ex.)
    5. Möjlighet att starta, pausa, avsluta spel. GameEngine borde alltså ha:
        - start_game(),
        - pause_game(), ✔
        - resume_game(),
        - stop_game() (spelet avslutas, men programmet körs) och
        - close_game() (avslutar allt)...
        - (RestartGame??))
    6. Implementera sätt att avgöra när ett spel är slut? Eller är det för spelspecifikt?
        - Typ en vector i GameEngine m. funktioner som gås igenom för varje loop, om varje funktion returnerar true så har man vunnit spelet och en funktion "won_game" utförs?
    7. Implementera något sätt att lägga in något som ska hända varje spel-tick, t.ex. att lägga till mer mat?
    8. PixelPerfectCollisionDetection!!!!
    9. Hur kan den som implementerar välja att använda Camera-grejen eller inte? typ att GameEngine borde ha:
        - set_camera_focus(Sprite& sprite);
            - Möjligt här att GameEngine kan ha en konstant statisk Sprite som är över hela leveln, osynlig (typ bara en rect då), som spelutvecklaren kan använda eller att det också finns set_camera_focus_on_all() typ
        - set_camera_width(int width);
        - set_camera_height(int height);
    10. Nästan alla funktioner i hela koden är publika!
    12. Vi ska använda getRes-constanten på någe vis.
    13. get_sound_channel (i GameEngine) kan i nuläget bara göra kanal-vektorn större, men inte mindre. Vet ärligt talat inte om det är ett problem i nuläget. Den kommer bara bli större *om det behövs*, och om det behövs, så kanske det kommer behövas en sådan stor vektor i framtiden också?
   
   
    

-- Spelet --
    1. "Dumma ner" NPCs, mer random, inte märker spelaren/att man är större,
delay på handlingar
    7. Något sätt att "vinna spelet" OBS
*/

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Food.h"
#include "GameEngine.h"
#include "LevelBackground.h"
#include "NPC.h"
#include "Player.h"

const int LEVEL_HEIGHT = 3500;
const int LEVEL_WIDTH = 3500;

void add_assets_loop(GameEngine*);

using dir_iterator = std::filesystem::recursive_directory_iterator;

// TODO: Ta reda på hur dyrt det är att kalla dynamic_cast i snabb intervall.
void expandPlayer(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) {
        p->expand(p);
    }
}

void minimizePlayer(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) p->minimize();
}



void use_player_boost(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) p->boost_pressed();
}

// Nedan är funktionerna som mappas till ett visst knapptryck. Mappen<SDLK,
// funcPtr> kommer att skickas till GameEngine. Om man trycker en knapp kommer
// SDL_EVENT loopen i GameEngine köra funktionen som mappats till knappen,
// funktionen är definierad i GameEngine klassen.

// TLDR : Man mappar knapptryck till funktioner i GameEngine. Implementationen
// förut innebar att man mappade knapptryck som utfördes på alla sprites i
// spelet.
void pause_game() { GameEngine::get_instance()->pause(SDLK_RETURN); }

void reset_game() { GameEngine::get_instance()->reset_game(); }

void quit_game() {
    GameEngine::get_instance()->quit();
}

void player_boost() {
    GameEngine::get_instance()->use_function_on_all_sprites(use_player_boost);
}

void minimize() {
    GameEngine::get_instance()->use_function_on_all_sprites(minimizePlayer);
}

void expand() {
    GameEngine::get_instance()->use_function_on_all_sprites(expandPlayer);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> assets;
    std::unordered_map<SDL_Keycode, funcPtr> keycode_map;
    
    GameEngine* game = GameEngine::get_instance(30, 1200, 800, LEVEL_WIDTH, LEVEL_HEIGHT);


    game->init_SDL_libraries();
    
    // WARNING----------------             WARNING: SDL reference in main!!! --------------- WARING
    game->init_SDL_window("GlobuleGobble", SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED);

    for (const auto& dirEntry : dir_iterator(constants::gResPath)) {
        if (dirEntry.is_regular_file()){
            std::cout << "added" << dirEntry.path().generic_string() << std::endl;
            assets.push_back(dirEntry.path().generic_string());
    }
    }

    game->load_assets(assets);


    LevelBackground* m = LevelBackground::get_instance(constants::gResPath + "images/fictionalspacebg.jpg",
                               game->get_level_width(), game->get_level_height());
    
    game->set_level_background(*m);

    //camera->set_focus_on_center(true);

    // make food and npcs randomly placed within level width and height, get a
    // seed for rand using time.
    srand(time(NULL));

    add_assets_loop(game);
    
    keycode_map.emplace(SDLK_UP, expand);
    keycode_map.emplace(SDLK_DOWN, minimize);
    keycode_map.emplace(SDLK_SPACE, player_boost);
    keycode_map.emplace(SDLK_ESCAPE, pause_game);
    keycode_map.emplace(SDLK_q, quit_game);
    keycode_map.emplace(SDLK_r, reset_game);

    game->load_keys(keycode_map);

    game->play_sound(constants::gResPath + "sounds/TillSpel.mp3",
                     GameEngine::get_instance()->get_sound_channel(), -1);

    Player* s = Player::get_instance();
    Camera* camera = Camera::get_instance(0, 0, game->get_screen_width(), game->get_screen_width());
    camera->set_focused_on(*s);
    
    while(game->run_game()){
        add_assets_loop(game);
    }
    return 0;
}

void add_assets_loop(GameEngine* game){
    Player* s = Player::get_instance();
    std::cout << s << std::endl;
    //Camera* camera = Camera::get_instance(0, 0, game->get_screen_width(), game->get_screen_height());
    game->add_sprite(*s);
    //camera->set_focused_on(*s);

    std::string planet;
    for (int i = 0; i < 300; i++) {

        if(i < 50)
            planet = "planet.png";
        else if( i >= 50 && i < 150)
            planet = "planet-earth.png";
        else if(i >= 150 && i < 225)
            planet = "jupiter.png";
        else
            planet = "venus.png";

        game->add_sprite(*Food::get_instance(constants::gResPath + "images/" + planet,
                                             rand() % LEVEL_WIDTH,
                                             rand() % LEVEL_HEIGHT, 19, 19));
    }

    for (int i = 0; i < 20; i++) {
        game->add_sprite(*NPC::get_instance(constants::gResPath + "images/alien3.png",
                                            rand() % LEVEL_WIDTH,
                                            rand() % LEVEL_HEIGHT, 21, 21));
    }


    std::cout << "ADDING PLAYER WITH " << s->area() << " AND x : " << s->getCenterX() << " y : " << s->getCenterY() << std::endl;
}