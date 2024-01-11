#ifndef CHARACTER_H
#define CHARACTER_H
#include <math.h>

#include <string>

#include "Sprite.h"

// Representerar karaktärer som rör på sig, spelbara eller inte.
class Character : public Sprite {
   public:
    Character(std::string path, int x, int y, int w, int h);
    virtual ~Character();
    virtual void tick() = 0;
    virtual void expand(int w, int h);
    virtual void minimize();
    virtual void char_move() = 0;
    void handle_collision();

   protected:
    void move_in_dir(double dir);
    double get_dir_to(double x, double y);
    void use_boost();

   private:
    int current_local_soundchannel;
    std::vector<int> local_soundchannels;
    int get_local_soundchannel();
    void play_eat_food_sound();
    void play_eat_character_sound();

    double get_vel() const;
    bool is_near_player() const;

    bool has_boost() const;
    void check_boost();
    void set_boost_speed(int speed);

    void center_camera();

    void kill(Sprite* killed_by = nullptr);

    int boost_counter;
    bool is_boosting;
    int boost_timer;
    int boost_speed;
};

#endif