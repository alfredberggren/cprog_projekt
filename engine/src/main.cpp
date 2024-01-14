#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Food.h"
#include "GameEngine.h"
#include "LevelBackground.h"
#include "NPC.h"
#include "Player.h"

#define LEVEL_HEIGHT 3500
#define LEVEL_WIDTH 3500
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1200
#define FRAMES_PER_SECOND 30
#define AMOUNT_OF_PLANETS 300
#define AMOUNT_OF_NPCs 20

using dir_iterator = std::filesystem::recursive_directory_iterator;

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
void pause_game() { GameEngine::get_instance()->pause(); }

void resume_game() { GameEngine::get_instance()->resume(); }

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
    //Get asset-paths and put them in vector
    for (const auto& dirEntry : dir_iterator(constants::gResPath)) {
        if (dirEntry.is_regular_file()){
            assets.push_back(dirEntry.path().generic_string());
        }
    }

    // -------------- SKAPAR EN GAMEENGINE OCH INITIERAR GRUNDLÄGGANDE SDL BIBLIOTEK OCH VIKTIGA SDL KOMPONENTER ------------------
    
    GameEngine* game = GameEngine::get_instance(FRAMES_PER_SECOND, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);
    game->init_SDL_libraries();
    game->init_SDL_window("GlobuleGobble", -1,-1);

    // -------------- SKICKAR IN ALLT SOM LIGGER I RESOURCES TILL MOTORN ---------------------------------------------------------- 

    game->load_assets(assets);

    // -------------- SKAPAR ETT LEVELBACKGROUND OBJEKT SOM TAR EN TEXTUR OCH SPELETS LEVEL WIDTH OCH HEIGHT OCH SÄTTER BAKGRUNDEN-
    LevelBackground* m = LevelBackground::get_instance(constants::gResPath + "images/fictionalspacebg.jpg", game->get_level_width(), game->get_level_height());
    game->set_level_background(*m);

    // -------------- FYLLER EN MAP MED KNAPPTRYCK SOM MAPPAS TILL FUNKTIONER OCH LADDAR IN DET I MOTORN --------------------------
    keycode_map.emplace(SDLK_UP, expand);
    keycode_map.emplace(SDLK_DOWN, minimize);
    keycode_map.emplace(SDLK_SPACE, player_boost);
    keycode_map.emplace(SDLK_ESCAPE, pause_game);
    keycode_map.emplace(SDLK_q, quit_game);
    keycode_map.emplace(SDLK_RETURN, resume_game);

    game->load_keys(keycode_map);

    // ------------- SKAPAR ETT SPELAROBJEKT OCH LÄGGER TILL DET I ENGINE ----------------------------------------------------------

    Player* s = Player::get_instance();
    game->add_sprite(*s);

    // ------------- SKAPAR ETT CAMERA OBJEKT OCH SÄTTER KAMERAN ATT FOKUSA PÅ EN SPRITE -------------------------------------------

    Camera* camera = Camera::get_instance(0, 0, game->get_screen_width(), game->get_screen_height());
    camera->set_focused_on(*s);
     
    // ------------- SKAPAR FOOD OCH NPC OBJEKT OCH LÄGGER TILL DEN I ENGINE -------------------------------------------------------
    srand(time(NULL));
    std::string planet;
    for (int i = 0; i < AMOUNT_OF_PLANETS; i++) {
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

    for (int i = 0; i < AMOUNT_OF_NPCs; i++) {
        game->add_sprite(*NPC::get_instance(constants::gResPath + "images/alien3.png",
                                            rand() % LEVEL_WIDTH,
                                            rand() % LEVEL_HEIGHT, 21, 21));
    }
    
    // --------------- LÄGGER TILL EN LJUDFIL I ENGINE OCH SPELAR DENNA ---------------------------------------------------------------
    game->play_sound(constants::gResPath + "sounds/TillSpel.mp3",
                     GameEngine::get_instance()->get_sound_channel(), -1);
    

    // --------------- KÖR SPELET UTIFRÅN DET SOM HAR LADDATS IN OCH FÖRBERETTS OVAN --------------------------------------------------
    game->run_game();


    // --------------- STÄDAR UPP ALLA ALLOKERADE RESURSER -----------------------------------------------------------------------------
    delete game;
    return 0;
}
