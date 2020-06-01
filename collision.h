#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


class collision
{
private:

public:
    collision();
    ~collision();

    //wskaznik na wektor platform
    const std::vector <sf::Sprite> *vector_wsk_platforms_ = nullptr;

    //wskaznik na bohatera
    const sf::Sprite *wsk_hero_collision_ = nullptr ;

    //

    //functions to set wsk
    void set_wsk_on_platforms(const std::vector <sf::Sprite> &vector);
    void set_wsk_on_hero(const sf::Sprite &hero);

    //check collision functions
    bool check_standing_collision(const sf::Sprite &hero,  const float &next_move);
    bool check_walking_collision(const sf::Sprite &hero, const float &next_move);

    //new functions na wskaznikach
    bool check_standing_collision(const float &next_move) const;
    bool check_walking_collision( const float &next_move) const;
    sf::Sprite *return_hero_collision();


};


#endif // COLLISION_H
