#ifndef LEVEL_BACKGROUND_H
#define LEVEL_BACKGROUND_H

#include <SDL2/SDL.h>
#include <string>

/*Class to be used for a background*/
class LevelBackground {

    public:
        static LevelBackground* get_instance(std::string backgroundpath, int level_width, int level_height) {return new LevelBackground(backgroundpath, level_width, level_height);}
        void draw() const;

    private:
        
        SDL_Rect rect;
        SDL_Texture* texture;
        LevelBackground(std::string, int, int);
    
};

#endif