/*TODO:
-- Spelmotor --
    X. Kolla ljudkanaler, vad är smartast att göra?
        - Implementerade någon sorts "hålla koll på vilka kanaler som används"-funktionalitet i gameengine. Vet inte hur smart det är egentligen.
    Z. Hur ska man kunna lägga till bakgrund? *typ* fixat?? Genom map.
    X. Hantera FPS!!!!!!! skickas nu in i engine constructor
    4. Dynamisk allokering, se till att saker o ting inte har publika konstruktorer om de inte ska ha det osv (Sprite t.ex.)
    5. Möjlighet att starta, pausa, avsluta spel. GameEngine borde alltså ha:
        - start_game(),
        - pause_game(),
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
    11. Sprite har en Kill-funktion (virtual pure dock), lite för spelspecifikt?
    12. Vi ska använda getRes-constanten på någe vis.
    13. get_sound_channel (i GameEngine) kan i nuläget bara göra kanal-vektorn större, men inte mindre. Vet ärligt talat inte om det är ett problem i nuläget. Den kommer bara bli större *om det behövs*, och om det behövs, så kanske det kommer behövas en sådan stor vektor i framtiden också?
    14. På samma sätt som vi implementerar ett sätt att ta bort sprites under loopen, måste vi göra liknande för att lägga till (enl. jozefs exempel)
    15. Förlåt, men egentligen borde vi göra samma map-lösning för alla sorters event... I nuläget kan spelutvecklaren bara göra att sina sprites kan reagera på knapptryck... 
    

-- Spelet --
    1. "Dumma ner" NPCs, mer random, inte märker spelaren/att man är större,
delay på handlingar
    X. Se till att NPCs inte kan gå utanför kartan ✔
    3. Tweaka hastigheter ✔
    4. Randomisera  vilka ljud som spelas när man äter (finns två i nuläget)
    5. "Zooma ut" kameran när spelare blivit för stor.
    6. Sätt spelaren i mitten av kartan vid spelstart
    7. Något sätt att "vinna spelet"


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

// TODO: Ta reda på hur dyrt det är att kalla dynamic_cast i snabb intervall.
void expandPlayer(Sprite* s) {
    if (Player* p = dynamic_cast<Player*>(s)) {
        p->expand(5, 5);
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

void player_boost() {
    GameEngine::get_instance()->add_key_function_for_sprite(use_player_boost);
}

void minimize() {
    GameEngine::get_instance()->add_key_function_for_sprite(minimizePlayer);
}

void expand() {
    GameEngine::get_instance()->add_key_function_for_sprite(expandPlayer);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> assets;
    std::unordered_map<SDL_Keycode, funcPtr> keycode_map;
    
    GameEngine* game = GameEngine::get_instance(30);

    game->init_SDL_libraries();
    game->init_SDL_window("GlobuleGobble", SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED, 640, 480);

    for (const auto& dirEntry : dir_iterator("resources")) {
        if (dirEntry.is_regular_file())
            assets.push_back(dirEntry.path().generic_string());
    }

    game->load_assets(assets);

    int LEVEL_WIDTH = 3500;
    int LEVEL_HEIGHT = 3500;

    Map* m = Map::get_instance("resources/images/spaceBackground.jpg",
                               LEVEL_WIDTH, LEVEL_HEIGHT);
    game->set_map(*m);

    Player* s = Player::get_instance();

    // make food and npcs randomly placed within level width and height, get a
    // seed for rand using time.
    srand(time(NULL));

    std::string planet;
    for (int i = 0; i < 300; i++) {

        if(i < 200)
            planet = "planet.png";
        else if( i >= 200 && i < 300)
            planet = "planet-earth.png";
        else if(i >= 300 && i < 500)
            planet = "jupiter.png";
        else
            planet = "venus.png";

        game->add_sprite(*Food::get_instance("resources/images/" + planet,
                                             rand() % LEVEL_WIDTH,
                                             rand() % LEVEL_HEIGHT, 15, 15));
    }

    for (int i = 0; i < 30; i++) {
        game->add_sprite(*NPC::get_instance("resources/images/circle.png",
                                            rand() % LEVEL_WIDTH,
                                            rand() % LEVEL_HEIGHT, 21, 21));
    }

    game->add_sprite(*s);

    keycode_map.emplace(SDLK_UP, expand);
    keycode_map.emplace(SDLK_DOWN, minimize);
    keycode_map.emplace(SDLK_SPACE, player_boost);
    keycode_map.emplace(SDLK_ESCAPE, pause_game);

    game->load_keys(keycode_map);

    game->play_sound("resources/sounds/TillSpel.mp3",
                     GameEngine::get_instance()->get_sound_channel(), -1);
    game->run_game();

    return 0;
}