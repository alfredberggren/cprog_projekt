#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

#include "Sprite.h"

// Representerar karaktärer som rör på sig, spelbara eller inte.
class Character : public Sprite {
   public:
    Character(std::string path, int x, int y, int w, int h)
        : Sprite(path, x, y, w, h, true),
          boost_counter(0),
          boost_timer(0),
          boost_speed(0) {}
    virtual void tick() = 0;
    virtual void expand(int w, int h);
    virtual void minimize();
    virtual void char_move() = 0;
    void handle_collision();

    void play_eat_food_sound();
    void play_eat_character_sound();

    void move_in_dir(double dir);
    double get_dir_to(double x, double y);

    double get_vel() const;
    bool is_near_player();
    virtual ~Character() {}

    bool has_boost() const;
    void check_boost();
    void use_boost();
    void set_boost_speed(int speed);

    void center_camera();

    void kill(Sprite* killed_by = nullptr);

   private:
    int boost_counter;
    bool is_boosting;
    int boost_speed;
    int boost_timer;
};

#endif