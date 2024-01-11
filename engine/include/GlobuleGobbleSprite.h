#ifndef GLOBULE_GOBBLE_SPRITE_H
#define GLOBULE_GOBBLE_SPRITE_H

#include "Camera.h"
#include "Sprite.h"

class GlobuleGobbleSprite : public Sprite {
   public:
    virtual void kill(Sprite& killed_by) = 0;

   protected:
    GlobuleGobbleSprite(std::string path_to_texture, int x, int y, int width,
                        int height, bool is_collidable);

   private:
    int get_rendered_x() const;
    int get_rendered_y() const;
};

#endif