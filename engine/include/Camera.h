#ifndef CAMERA_H
#define CAMERA_H

#include "Sprite.h"
#include "GameEngine.h"

class Camera {
    private:
        Camera(int x, int y, int w, int h, const Sprite& focused);
        
        SDL_Rect camera_rect;
        const Sprite* focused_on;
        static Camera* instance;
        
    public:
        void center();
        const Sprite* get_focused_on();
        
        /*Use to create the Camera-instance*/
        static Camera* create(int, int, int, int, const Sprite&);
        
        /*Will return a nullpointer if Camera has not been initiated*/
        static Camera* get_instance();

        void set_focused_on(const Sprite&);

        void set_x(int x);
        void set_y(int y);
        void set_h(int h);
        void set_w(int w);

        int get_x() const;
        int get_y() const;
        int get_h() const;
        int get_w() const;
    
};




#endif