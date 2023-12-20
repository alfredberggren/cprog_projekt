#include "GameEngine.h"

void GameEngine::loadWav(std::string path) {
    std::cout << "Loading wav: " << path << std::endl;
}

void GameEngine::loadPng(std::string path) {
    std::cout << "Loading png: " << path << std::endl;
}

void GameEngine::loadMp3(std::string path) {
    std::cout << "Loading mp3: " << path << std::endl;
}

void GameEngine::loadJpg(std::string path) {
    std::cout << "Loading jpg: " << path << std::endl;
}

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::run_game() {
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_RenderClear(sys.renderer);
        SDL_RenderPresent(sys.renderer);
    }
}

void GameEngine::load_assets(std::vector<std::string> assets) {
    for (auto asset : assets) {
        if (asset.find(".png") != std::string::npos) {
            loadPng(asset);
        } else if (asset.find(".jpg") != std::string::npos) {
            loadJpg(asset);
        } else if (asset.find(".mp3") != std::string::npos) {
            loadMp3(asset);
        } else if (asset.find(".wav") != std::string::npos) {
            loadWav(asset);
        } else {
            std::cout << "Unknown file type: " << asset << std::endl;
        }
        
        SDL_Surface* surface = IMG_Load(asset.c_str());
        if (surface == nullptr) {
            std::cout << "Error loading image: " << asset << std::endl;
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            continue;
        }
        SDL_Texture* texture =
            SDL_CreateTextureFromSurface(sys.renderer, surface);
        if (texture == nullptr) {
            std::cout << "Error creating texture from surface: " << asset
                      << std::endl;
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            continue;
        }
        SDL_FreeSurface(surface);
        SpriteManager::get_instance()->loadedTextures[asset] = texture;
    }
}