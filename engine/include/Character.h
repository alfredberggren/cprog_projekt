#ifndef CHARACTER_H
#define CHARACTER_H
#include <math.h>

#include <string>
#include <vector>

#include "Constants.h"
#include "GlobuleGobbleSprite.h"

// Representerar karaktärer som rör på sig, spelbara eller inte.
class Character : public GlobuleGobbleSprite
{
public:
    virtual ~Character();
    virtual void tick() override;
    virtual void expand(Sprite* eaten_sprite);
    virtual void minimize();
    virtual void char_move() = 0;
    void handle_collision();

protected:
    Character(std::string path, int x, int y, int w, int h);
    void move_in_dir(double dir);
    double get_dir_to(double x, double y);
    void use_boost();

   private:
    static const int MAX_BOOST = 15;
    static const int BOOST_SPEED = 10;
    static const int BOOST_LENGTH = 25;
    static const int MINIMIZE_AMOUNT = 5;
    static const int EXPAND_AMOUNT = 10;
    static const int NEAR_PLAYER_RADIUS = 250;

    int boost_counter;
    int boost_timer;
    int boost_speed;
    
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


    void die(Sprite& killed_by) override;


};

#endif