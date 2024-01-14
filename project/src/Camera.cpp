#include "Camera.h"

Camera *Camera::get_instance(int x, int y, int w, int h)
{
    if (instance == nullptr)
    {
        instance = new Camera(x, y, w, h);
    }
    return instance;
}

Camera::Camera(int x, int y, int w, int h) : camera_rect{x, y, w, h} {}

const Sprite *Camera::get_focused_on()
{
    return focused_on;
}

void Camera::set_focused_on(const Sprite &sprite)
{   centering_on_sprite = true;
    focused_on = &sprite;
}

void Camera::set_x(int x) { camera_rect.x = x; }
void Camera::set_y(int y) { camera_rect.y = y; }
void Camera::set_h(int h) { camera_rect.h = h; }
void Camera::set_w(int w) { camera_rect.w = w; }

int Camera::get_x() const { return camera_rect.x; }
int Camera::get_y() const { return camera_rect.y; }
int Camera::get_w() const { return camera_rect.w; }
int Camera::get_h() const { return camera_rect.h; }

void Camera::center_on_sprite()
{
    if ((focused_on != nullptr) && centering_on_sprite)
    {
        camera_rect.x = (focused_on->get_rect()->x + focused_on->get_rect()->w / 2) - GameEngine::get_instance()->get_screen_width() / 2;
        camera_rect.y = (focused_on->get_rect()->y + focused_on->get_rect()->h / 2) - GameEngine::get_instance()->get_screen_height() / 2;

        // Håll kameran inom spelplanen
        if (camera_rect.x < 0)
        {
            camera_rect.x = 0;
        }
        if (camera_rect.y < 0)
        {
            camera_rect.y = 0;
        }
        if (camera_rect.x > GameEngine::get_instance()->get_level_width() - camera_rect.w)
        { 
            camera_rect.x = GameEngine::get_instance()->get_level_width() - camera_rect.w;
        }
        if (camera_rect.y > GameEngine::get_instance()->get_level_height() - camera_rect.h)
        {
            camera_rect.y = GameEngine::get_instance()->get_level_height() - camera_rect.h;
        }
    }
}

void Camera::set_focus_on_center(bool focus) {
    centering_on_sprite = !focus;
    camera_rect.x = GameEngine::get_instance()->get_level_width() / 2 - camera_rect.w / 2;
    camera_rect.y = GameEngine::get_instance()->get_level_height() / 2 - camera_rect.h / 2;
}

Camera* Camera::instance = nullptr;
