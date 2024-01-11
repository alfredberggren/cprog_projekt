#include "LevelBackground.h"
#include "Camera.h"

LevelBackground::LevelBackground(std::string backgroundpath, int width, int height) : rect{0, 0, width, height} {
    texture = AssetManager::get_instance()->get_texture(backgroundpath);
}

void LevelBackground::draw() const {
    std::cout << "ritar bakgrund" << -(Camera::get_instance()->get_x()) << std::endl;
    SDL_Rect bRect = {-(Camera::get_instance()->get_x()), -(Camera::get_instance()->get_y()), rect.w, rect.h};
    SDL_RenderCopy(SYSTEM.renderer, texture, NULL/*&Camera::get_instance()->get_rect()*/, &bRect);
}

