#include "Food.h"

Food::Food(std::string path, int x, int y, int w, int h): GlobuleGobbleSprite(path, x, y, w, h, true) {}

Food* Food::get_instance(std::string path, int x, int y, int w, int h){
    return new Food(path, x, y, w, h);
}

void Food::die(Sprite& killed_by) {
    setX(rand() % 3500);
    setY(rand() % 3500);
}