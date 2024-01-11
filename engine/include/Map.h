#ifndef MAP_H
#define MAP_H

#include "Sprite.h"
#include "System.h"

/*Class to be used for a background*/
class Map : public Sprite{

    public:
        static Map* get_instance(std::string backgroundpath, int screen_width, int screen_height) {return new Map(backgroundpath, screen_width, screen_height);}

        void mouseMoved(double, double) override {}
        void tick() override {}
        void draw() const override;

        

    private:
        Map(std::string, int, int);
    
};

#endif