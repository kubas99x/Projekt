#include "new_enemies.h"
#include "iostream"
new_enemies::new_enemies()
{

}

new_enemies::new_enemies(const enemy_type &type ,float pos_x, float pos_y ,float distance, float time)
{
    this->init_variables ();
    this->walk_distance_ = distance;
    this->waiting_time_start_ = time;
    this->enemy_type_=type;
    this->start_position_x_=pos_x;
    this->start_position_y_=pos_y;

    this->download_textures ();
    this->set_animations ();
    this->set_enemy ();

}

void new_enemies::init_variables()
{
    this->enemy_step_dying_=0;
    this->enemy_step_standing_=0;
    this->enemy_step_attack_=0;
    this->was_attacked_ = false;
    this->dead_ = false;
    this->moving_left_ = false;
    this->attacking_ = false;
    this->can_attack_ = true;
    this->hited_hero_ = false;
}


void new_enemies::download_textures()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        texture_.emplace_back(get_textures("textures/skeleton_standing.png"));              //0
        texture_.emplace_back(get_textures("textures/skeleton_die.png"));                   //1
        texture_.emplace_back(get_textures("textures/skeleton_standing_left.png"));        //2
        texture_.emplace_back(get_textures ("textures/skeleton_attack_left.png"));         //3
    }
}

void new_enemies::set_enemy()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        enemy_action_=enemy_action::standing;
        enemy_sprite_.setTexture (texture_[0]);
        enemy_sprite_.setTextureRect (animations_[enemy_action::standing][0]);
        enemy_sprite_.setPosition (start_position_x_, start_position_y_);
        enemy_sprite_.setScale (3.5,3.5);
        distance_=walk_distance_;
        move_left=true;
        waiting_time_=waiting_time_start_;
        hp_=100;
        waiting_for_attack_=3;
    }
}
void new_enemies::set_animations()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        std::vector <sf::IntRect> tmp_vector;
        for(int i=0; i<24*11; i+=24)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,24,36));
        }
        animations_.emplace(enemy_action::standing,tmp_vector);
        animations_.emplace(enemy_action::standing_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=0; i<33*16; i+=33)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,34,32));

        }
        animations_.emplace(enemy_action::dying,tmp_vector);

        tmp_vector.clear ();
        int height = 36;
        tmp_vector.emplace_back(sf::IntRect(2,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(46,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(90,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(123,0,30,height));
        tmp_vector.emplace_back(sf::IntRect(160,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(200,0,34,height));
        tmp_vector.emplace_back(sf::IntRect(244,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(288,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(332,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(373,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(415,0,40,height));
        tmp_vector.emplace_back(sf::IntRect(468,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(510,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(554,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(595,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(680,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(723,0,35,height));

        animations_.emplace(enemy_action::attack_left,tmp_vector);


    }
}



void new_enemies::update_enemy_frame()
{
    enemy_frame_time_+=time_.asSeconds ();
    if(enemy_frame_time_>=1.0f/13.0f && (enemy_action_==enemy_action::standing || enemy_action_==enemy_action::standing_left ))
    {
        enemy_step_standing_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
    if(enemy_frame_time_>=1.0f/8.0f && enemy_action_==enemy_action::dying )
    {
        enemy_step_dying_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
    if(enemy_frame_time_>=1.0f/8.0f && enemy_action_==enemy_action::attack_left )
    {
        enemy_step_attack_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
        if(enemy_step_attack_>=6 && enemy_step_attack_<=12)
        {
            can_deal_dmg_=true;
        }
        else
        {
            can_deal_dmg_=false;
        }
    }
}
void new_enemies::choose_enemy_animation()
{
    if(this->enemy_animation_change_)
    {
        if(enemy_action_==enemy_action::standing)
        {
            if(this->enemy_step_standing_>=animations_[enemy_action::standing].size ()-1)
            {
                enemy_step_standing_=0;
            }
            this->enemy_sprite_.setTexture (texture_[0]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::standing][this->enemy_step_standing_]);
        }

        if(enemy_action_==enemy_action::standing_left)
        {
            if(this->enemy_step_standing_>=animations_[enemy_action::standing_left].size ()-1)
            {
                enemy_step_standing_=0;
            }
            this->enemy_sprite_.setTexture (texture_[2]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::standing_left][this->enemy_step_standing_]);
        }

        if(enemy_action_==enemy_action::dying)
        {
            if(this->enemy_step_dying_>=animations_[enemy_action::dying].size ()-1)
            {
                this->dead_=true;
            }
            this->enemy_sprite_.setTexture (texture_[1]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::dying][this->enemy_step_dying_]);
        }
        if(enemy_action_==enemy_action::attack_left)
        {
            if(this->enemy_step_attack_>=animations_[enemy_action::attack_left].size ()-1)
            {
                enemy_step_attack_=0;
                attacking_ = false;
            }
            this->enemy_sprite_.setTexture (texture_[3]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::attack_left][animations_[enemy_action::attack_left].size ()-1 - this->enemy_step_attack_]);

        }
    }
    enemy_animation_change_=false;
}

void new_enemies::move_enemy()
{
    if(enemy_action_!=enemy_action::dying && !attacking_)
    {
        if(waiting_time_<=0)
        {
            if(move_left)
            {
                enemy_action_=enemy_action::standing_left;

                enemy_sprite_.move (-1,0);
                distance_-=1;
                if(distance_<=0)
                {
                    distance_=walk_distance_;
                    waiting_time_=waiting_time_start_;
                    move_left=false;
                }
            }
            else
            {
                enemy_action_=enemy_action::standing;
                enemy_sprite_.move (1,0);
                distance_-=1;
                if(distance_<=0)
                {
                    distance_=walk_distance_;
                    waiting_time_=waiting_time_start_;
                    move_left=true;
                }
            }
        }
    }

}

void new_enemies::attack_stuff()
{
   waiting_for_attack_-=time_.asSeconds ();
   if(waiting_for_attack_<=0)
   {
       hited_hero_ = false;
       can_attack_=true;
       waiting_for_attack_=5;
   }

}

void new_enemies::check_hp()
{
    if(this->hp_<=0)
    {
        enemy_action_=enemy_action::dying;
    }
}



void new_enemies::update_enemy()
{
    this->time_=clock.restart ();
    waiting_time_-=time_.asSeconds ();

    this->update_enemy_frame ();
    this->choose_enemy_animation ();
    if(enemy_type_==enemy_type::skeleton)
    {
        this->move_enemy ();
    }
    if(attacking_)
    {
        this->enemy_action_=enemy_action::attack_left;
    }
    if(!can_attack_ && !attacking_)
    {
        attack_stuff ();
    }
    this->check_hp ();
}

sf::Sprite new_enemies::return_enemy_sprite()
{
    return enemy_sprite_;
}

void new_enemies::render(sf::RenderWindow &window)
{
    window.draw (enemy_sprite_);
}


