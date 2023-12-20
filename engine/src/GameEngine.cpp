#include "GameEngine.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine() {
    
}

GameEngine::~GameEngine() {}

void GameEngine::run_game(){
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else if(event.type == SDL_KEYDOWN){
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