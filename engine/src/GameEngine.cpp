#include "GameEngine.h"

#include <SDL2/SDL_mixer.h>

#include <utility>

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

// TODO : Fixa returvärden!

bool GameEngine::init_SDL_libraries() {
    return SYSTEM.initSDLComponents();
    
}

bool GameEngine::init_SDL_window(std::string windowTitle, int xPosition,
                                 int yPosition, int width, int height) {
   
    return SYSTEM.initWindowAndRenderer(windowTitle, xPosition, yPosition, width,
                                 height);
    
}

/*Plays the sound from specified soundpath the specified amount of repeats. Use -1 for infinite repeats.
Returns the channel the sound is playing on (int), which can be used for stopping sound later. */
int GameEngine::play_sound(const std::string& soundpath, int repeats) const {
    return Mix_PlayChannel(-1,
                    AssetManager::get_instance()
                        ->get_sound(soundpath),
                    repeats);
}

/*Stops a sound playing on specified soundchannel. 
Use -1 to stop all channels.*/
void GameEngine::stop_sound(int soundchannel) const {
    Mix_HaltChannel(soundchannel);
}


void GameEngine::run_game() {

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                // Kolla om KEY finns i keyMapping, isåfall hämta den och skicka
                // funktionen till AssetManager
                if (keyMapping->count(event.key.keysym.sym) > 0) {
                    AssetManager::get_instance()->handleKeyEvent(
                        keyMapping->at(event.key.keysym.sym));
                }

            } else if (event.type == SDL_MOUSEMOTION) {
                AssetManager::get_instance()->mouseMovedAll(event.motion.x,
                                                            event.motion.y);
            }
        }

        SDL_RenderClear(SYSTEM.renderer);

        AssetManager::get_instance()->tickAll();
        AssetManager::get_instance()->remove_marked();
        AssetManager::get_instance()->drawAll();

        SDL_RenderPresent(SYSTEM.renderer);
        SDL_Delay(62.5);
    }
}

void GameEngine::load_keys(std::unordered_map<SDL_Keycode, funcPtr>& map) {
    keyMapping = &map;
}

/*Loads assets from the vector*/
void GameEngine::load_assets(std::vector<std::string> assets) {
    for (auto asset : assets) {
        if ((asset.find(".png") != std::string::npos) ||
            (asset.find(".jpg") != std::string::npos)) {
            load_img(asset);
        } else if ((asset.find(".mp3") != std::string::npos) ||
                   (asset.find(".wav") != std::string::npos)) {
            load_sound(asset);
        } else {
            std::cerr << "Unknown file type: " << asset << std::endl;
        }

        // TODO: add pathway?
        // TODO: Figure out what the above means, write better comments
    }
}

// TODO: could just return the texture itself
/*Loads an image from the path*/
bool GameEngine::load_img(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Error loading image: " << path << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Behöver kanske inte vara klassmedlem
    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(SYSTEM.renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Error creating texture from surface: " << path
                  << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    AssetManager::get_instance()->add_texture(path, texture);
    SDL_FreeSurface(surface);
    
    return true;
}

/*Loads a sound from the path, as a Chunk*/
bool GameEngine::load_sound(std::string path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

    if (chunk == nullptr) {
        std::cerr << "Error loading sound: " << path << std::endl;
        std::cerr << "SDL error: " << Mix_GetError();
        return false;
    }

    AssetManager::get_instance()->add_sound(path, chunk);
    return true;
}

void GameEngine::add_sprite(Sprite& sprite) {
    AssetManager::get_instance()->add(sprite);
}

GameEngine* GameEngine::get_instance() {
    if (instance == nullptr) {
        instance = new GameEngine();
    }
    return instance;
}
