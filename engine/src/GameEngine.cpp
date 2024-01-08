#include "GameEngine.h"

#include <SDL2/SDL_mixer.h>

#include <utility>

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
    std::cout << "Destroying GameEngine" << std::endl;
    for (auto pair : AssetManager::get_instance()->loaded_textures) {
        SDL_DestroyTexture(pair.second);
    }
    for (auto pair : AssetManager::get_instance()->loaded_sounds) {
        Mix_FreeChunk(pair.second);
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::run_game() {
    Mix_PlayChannel(-1,
                    AssetManager::get_instance()
                        ->loaded_sounds["resources/sounds/TillSpel.mp3"],
                    -1);  // REMOVE REMOVE REMOVE

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
        AssetManager::get_instance()->drawAll();

        SDL_RenderPresent(SYSTEM.renderer);
        SDL_Delay(150);
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
            std::cout << "Unknown file type: " << asset << std::endl;
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
        std::cout << "Error loading image: " << path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Behöver kanske inte vara klassmedlem
    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(SYSTEM.renderer, surface);
    if (texture == nullptr) {
        std::cout << "Error creating texture from surface: " << path
                  << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    AssetManager::get_instance()->loaded_textures.insert(
        std::make_pair(path, texture));
    SDL_FreeSurface(surface);
    if (AssetManager::get_instance()->loaded_textures[path] == nullptr) {
        std::cout << "Texturen är null efter inlagd" << std::endl;
        return false;
    }
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

    AssetManager::get_instance()->loaded_sounds.insert(
        std::make_pair(path, chunk));
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
