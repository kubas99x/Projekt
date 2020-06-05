#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "background.h"
#include "platform.h"
#include "player.h"
#include "collision.h"
#include "new_enemies.h"
class Game
{
private:
    //Window stuff
    sf::RenderWindow * window;
    sf::Clock clock_;
    sf::Time time_;

    //Backgrounds
    background *background_;

    //Platforms
    platform *platform_;

    //Player
    player * player_;

    //Collision
    collision * collision_;

    //enemies
    std::vector <new_enemies*>  enemies_vector_;


    //Private void functions
    void initWindow();
    void initVariables();
    void check_all_collisions();
    void add_enemies();
    void check_enemy_hp_();

public:
    Game();
    ~Game();

    //Public variables
    float hero_x_position_;

    //Public functions
    void updatePollEvents();
    void update();
    void gamerender();

    //Bool functions
    bool game_is_running  () const ;
};

#endif // GAME_H
