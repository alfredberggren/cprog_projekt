#include "Map.h"

Map::Map(std::string backgroundpath, int width, int height) : Sprite(backgroundpath, 0, 0, width, height, false) {}

void Map::draw() {
    SDL_Rect bRect = {-camera.x, -camera.y, rect.w, rect.h};
    SDL_RenderCopy(SYSTEM.renderer, texture, NULL, &bRect);
}

