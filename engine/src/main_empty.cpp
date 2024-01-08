#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"

#define PI 3.14

using dir_iterator = std::filesystem::recursive_directory_iterator;

class Player : public Sprite {
    // TODO: singleton

   public:
    Player(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h) {}

    double getDirToMouse() {
        double radian =
            std::atan2(mouse_x - getCenterX(), mouse_y - getCenterY());
        double angle = radian * (180 / PI);
        if (angle < 0.0) {
            angle += 360.0;
        }
        std::cout << angle << std::endl;
        return angle;
    }

    void tick() {
        double dir = getDirToMouse();
        double x = std::cos(dir * (PI / 180));
        double y = std::sin(dir * (PI/ 180));
        std::cout << "X: " << x << " Y: " << y << std::endl;
        // move(std::cos(PI * 2 * dir / 360) * 2.0,
        // std::sin(PI * 2 * dir / 360) * 2.0);
    }

    void mouseMoved(double x, double y) {
        mouse_x = x;
        mouse_y = y;
    }

   private:
    double mouse_x;
    double mouse_y;
};

int main(int argc, char* argv[]) {
    std::string s1 = "Hejsan";
    std::cout << s1 << std::endl;

    SYSTEM.initSDLComponents();

    GameEngine* game = GameEngine::get_instance();

    std::vector<std::string> assets;

    for (const auto& dirEntry : dir_iterator("resources")) {
        if (dirEntry.is_regular_file())
            assets.push_back(dirEntry.path().generic_string());
    }

    game->load_assets(assets);

    Player* s = new Player("resources/images/bg.jpg", 320, 240, 100, 100);

    game->add_sprite(*s);

    game->run_game();

    return 0;
}