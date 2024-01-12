#ifndef CAMERA_H
#define CAMERA_H

#include "Sprite.h"
#include "GameEngine.h"


class Camera {
    private:
        Camera(int x, int y, int w, int h);
        bool centering_on_sprite;
        SDL_Rect camera_rect;
        const Sprite* focused_on;
        static Camera* instance;
        
    public:
        void center_on_sprite();
        const Sprite* get_focused_on();
        
        
        /*Will return a nullpointer if Camera has not been initiated.
        Combine with set_focus_on to set its focus on a sprite*/
        static Camera* get_instance(int x = 0, int y = 0, int w = 0, int h = 0);

        void set_focused_on(const Sprite&);
        void set_focus_on_center(bool focus);
        void set_x(int x);
        void set_y(int y);
        void set_h(int h);
        void set_w(int w);

        int get_x() const;
        int get_y() const;
        int get_h() const;
        int get_w() const;

        const SDL_Rect& get_rect() const { return camera_rect; }
    
};




#endif