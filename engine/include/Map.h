#ifndef MAP_H
#define MAP_H

#include "Sprite.h"

class Map : public Sprite{
    public:
        Map(std::string path, int x, int y, int w, int h) : Sprite(path, x, y, w, h, false), MAP_WIDTH(w), MAP_HEIGHT(h){
            screen_rect.w = SCREEN_WIDTH;
            screen_rect.h = SCREEN_HEIGHT;
        }

        void tick(){
            
        }

        void mouseMoved(double x, double y) override{

        }

        void draw() override{
            //SDL_RenderCopyEx(SYSTEM.renderer, texture, &screen_rect, NULL, );
        }
    private:
        const int MAP_WIDTH;
        const int MAP_HEIGHT;

        const int SCREEN_WIDTH = 640;
        const int SCREEN_HEIGHT = 480;

        SDL_Rect screen_rect;
};

#endif