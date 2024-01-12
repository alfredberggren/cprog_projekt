#include "System.h"
#include <iostream>


System::System() {
    
}

/*Initializes all needed SDL-components, and returns true if successful, false otherwise. Please quit everything if false.*/
bool System::initSDLComponents(){
    bool check = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 || IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        check = false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize Mix Audio: %s", Mix_GetError());
        check = false;
    }

    if (check){
        std::cout << "SYSTEM: \n\tSDL components initialized successfully" << std::endl;
    } else {
        std::cerr << "SYSTEM: \n\tSDL components failed initialization" << std::endl;
    }
    return check;
}

bool System::initWindowAndRenderer(std::string title, int xPos, int yPos, int width, int height){
    bool check = true;

    if (xPos < 0 || yPos < 0) {
        xPos = SDL_WINDOWPOS_CENTERED;
        yPos = SDL_WINDOWPOS_CENTERED;
    }

    //TODO: Change hardcoded window-text and size to use arguments
    window = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        check = false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        check = false;
    }
    if (check){
        std::cout << "SYSTEM: \n\tWindow and Renderer initialized successfully" << std::endl;
    } else {
        std::cerr << "SYSTEM: \n\tWindow and Renderer failed initialization" << std::endl;
    }
    return check;
}

System::~System() {
    std::cout << "SYSTEM:" << std::endl;
    SDL_DestroyRenderer(renderer);
    std::cout << "\t- Destroyed renderer" << std::endl;
    SDL_DestroyWindow(window);
    std::cout << "\t- Destroyed window" << std::endl;
    IMG_Quit();
    std::cout << "\t- Quit IMG" << std::endl;
    Mix_CloseAudio();
    std::cout << "\t- Closed  audio" << std::endl;
    Mix_Quit();
    std::cout << "\t- Quit mix" << std::endl;
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    std::cout << "\t- Quit VIDEO and AUDIO" << std::endl;
    
    SDL_Quit();
    std::cout << "\t- Quit SDL" << std::endl;
}

System SYSTEM;