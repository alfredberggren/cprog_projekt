#include "Map.h"

Map::Map(std::string backgroundpath, int width, int height) : Sprite(backgroundpath, 0, 0, width, height, false), MAP_WIDTH(width), MAP_HEIGHT(height) {}

void Map::draw() const {
    SDL_Rect bRect = {-camera.x, -camera.y, rect.w, rect.h};
    SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &bRect);
}

