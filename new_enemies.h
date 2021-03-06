#ifndef NEW_ENEMIES_H
#define NEW_ENEMIES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "texture_functions.h"
#include "enum_classes.h"

#include <vector>
#include <map>

class new_enemies : public texture_functions
{
private:
    //czas
    sf::Clock clock;
    sf::Time time_;

    //enemy sprite
    sf::Sprite enemy_sprite_;

    //enemy type
    enemy_type enemy_type_;

    //enemy action
    enemy_action enemy_action_;

    //texture
    std::vector<sf::Texture> texture_;

    //mapa z roznymi animacjami (ktora bedzie zawiera kwadraty ktore trzeba wziac z tekstury)
    std::map <enemy_action,std::vector<sf::IntRect>> animations_;

    //health bar bossa
    sf::Sprite health_bar_;
    std::vector <sf::IntRect> health_animations_;

    //sound effects
    std::vector <sf::SoundBuffer> buffer;
    sf::Sound sound;
    void set_sound_effects();

    //variables
    float enemy_frame_time_;
    int enemy_step_standing_;
    int enemy_step_dying_;
    int enemy_step_attack_;
    int enemy_step_walking_;
    bool enemy_animation_change_;
    bool moving_left_;                  //do ustalania animacji

    float waiting_time_;                //czas przez ktory wrog stoi i czeka w miejscu
    float distance_;
    float start_position_x_;
    float start_position_y_;
    float walk_distance_;
    float waiting_time_start_;
    float waiting_for_attack_;
    float velocity_;

    //functions
    void download_textures();
    void set_animations();
    void set_enemy();
    void update_enemy_frame();
    void choose_enemy_animation();
    void move_enemy();
    void check_hp();
    void init_variables();
    void attack_stuff();
    void move_wolf();

public:
    //Constructors
    new_enemies();
    new_enemies(const enemy_type &type,float pos_x, float pos_y , float distance, float time);

    //enemy variables
    int hp_;
    bool dead_;
    bool was_attacked_;
    bool attacking_;                //czy postac jest w trakcie ataku
    bool can_attack_;               //czy postac moze juz zaatakowac
    bool hited_hero_;
    bool can_deal_dmg_;             //by zadawal dmg tylko kiedy jest animacja tego ataku zamachniecia
    bool attack_right_;
    bool wolf_running_;
    bool move_left;

    void render(sf::RenderWindow &window);
    void update_enemy();
    enemy_type return_enemy_type();
    sf::Sprite return_enemy_sprite();
};

#endif // NEW_ENEMIES_H
