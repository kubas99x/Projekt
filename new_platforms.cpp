#include "new_platforms.h"
#include <iostream>
new_platform::new_platform()
{

}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height, const platform_type &type)
{
    this->type_=type;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y, width, height);
}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, const platform_type &type )
{
    this->type_=type;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y);
}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, const platform_type &type, bool moving , float moving_distance , bool movig_right)
{
    this->type_=type;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y);
    this->moving_=moving;
    this->distance_=moving_distance;
    this->distance_tmp_=moving_distance;
    this->moving_right=movig_right;

}

//platformy z dzwigniami
new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, float arm_x, float arm_y, const platform_type &type, bool interaction , bool moving_left_right)
{

    this->type_=type;
    this->interaction_=interaction;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y);
    set_arm_interaction_ (arm_x,arm_y);
    this->moving_left_right_=moving_left_right;
    if(moving_left_right_)
    {
        if(type_==platform_type::rock_pion)
        {
            distance_=sprite_.getGlobalBounds ().height;
        }
        else
        {
            distance_=sprite_.getGlobalBounds ().width;
        }
    }
    else
    {
        distance_=400;
    }
    distance_tmp_=distance_;
}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height, float arm_x, float arm_y, const platform_type &type, bool interaction )
{

    this->type_=type;
    this->interaction_=interaction;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y, width, height);
    set_arm_interaction_ (arm_x,arm_y);
    if(type_==platform_type::rock_pion)
    {
        distance_=sprite_.getGlobalBounds ().height + 50;
    }
    else
    {
        distance_=sprite_.getGlobalBounds ().width + 50;
    }
    distance_tmp_=distance_;
}



new_platform::~new_platform()
{

}



void new_platform::download_textures ()
{
    /*
     pobieranie odpowiedniej tekstury w zaleznosci od typu platformy
     */
    sf::Texture tmp;
    switch(type_)
    {
    case platform_type::grass:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(320 , 15, 175, 65));        //tekstura samej  trawy z ziemia by mozna powielac
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::wood:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(20, 27 , 250 , 35));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::rock_with_gras:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(683 , 15, 220, 65));
        texture_=tmp;
        texture_.setRepeated (false);
        break;
    }
    case platform_type::rock_pion:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(21 , 80, 120, 65));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::rock:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(780 , 15, 120, 65));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::grass_pocz:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(535 , 15, 130, 65));
        texture_=tmp;
        texture_.setRepeated (false);
        break;
    }
    case platform_type::spikes:
    {
        tmp.loadFromFile ("textures/Assets.png", sf::IntRect(79 , 148, 16, 12));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    default:
    {
        std::cout<<"Cos poszlo nie tak"<<std::endl;
        break;
    }
    }
}

void new_platform::set_sprites(float pos_x, float pos_y, float scale_x, float scale_y)
{
    /*
     ustawianie platform, ich tekstury, pozycji i skali
     */
    sprite_.setTexture (texture_);
    sprite_.setPosition (pos_x,pos_y);
    sprite_.setScale (scale_x,scale_y);
}

void new_platform::set_sprites(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height)
{
    if(type_==platform_type::spikes)
    {
        damage_platform=true;
    }
    sprite_.setTexture (texture_);
    sprite_.setPosition (pos_x,pos_y);
    sprite_.setScale (scale_x,scale_y);
    sprite_.setTextureRect (sf::IntRect(0,0,width, height));

}

void new_platform::set_arm_interaction_(float x, float y)
{
    /*
     ustawianie dzwigni, pozycji, tekstury, skali
     */
    sf::Texture tmp;
    tmp.loadFromFile ("textures/Assets.png", sf::IntRect(64 , 84, 33, 12));
    texture_interaction_=tmp;
    texture_interaction_.setRepeated (false);
    sprite_interaction_.setTexture (texture_interaction_);
    sprite_interaction_.setTextureRect (sf::IntRect(0,0,17,12));                    //wybranie dzwigni w lewo
    sprite_interaction_.setPosition (x,y);
    sprite_interaction_.setScale (3,3);

}

void new_platform::chagne_arm_interaction()
{
    /*
     jezeli zostala nacisnieta dzwignia to zareaguj
     */
    changed_arm_=true;
    sprite_interaction_.setTextureRect (sf::IntRect(17,0,17,12));                    //wybranie dzwigni w lewo

}

void new_platform::move_platform(float time)
{
    /*
     ruszanie platformy jezeli zostala nacisnieta dzwignia
     */
    if(moving_left_right_)
    {
        if(type_==platform_type::rock_pion)
        {
            if(distance_>0)
            {
                this->sprite_.move (0,-1*velocity_*time);
                distance_-=velocity_*time;
            }
        }
        else
        {
            if(distance_>0)
            {
                this->sprite_.move (-1*velocity_*time,0);
                distance_-=velocity_*time;
            }
        }
    }
    else
    {
        if(distance_>0)
        {
            this->sprite_.move (0,1*velocity_*time);
            distance_-=velocity_*time;
        }
    }
}

void new_platform::moving_side_to_side(float time)
{
    /*
     ruch platform ktore ruszaja sie lewo/prawo
     */
    if(moving_right)
    {
        if(0.3*velocity_*time<5)               //na wypadek jakby czas byl bardzo duzy
        {
            sprite_.move (0.3*velocity_*time,0);
            distance_-=0.3*velocity_*time;
        }
        else
        {
            sprite_.move (3,0);
            distance_-=3;
        }
        if(distance_<=0)
        {
            moving_right=false;
            distance_=distance_tmp_;
        }
    }
    else
    {
        if(0.3*velocity_*time<5)               //na wypadek jakby czas byl bardzo duzy
        {
            sprite_.move (-0.3*velocity_*time,0);
            distance_-=0.3*velocity_*time;
        }
        else
        {
            sprite_.move (-3,0);
            distance_-=3;
        }
        if(distance_<=0)
        {
            moving_right=true;
            distance_=distance_tmp_;
        }
    }
}

void new_platform::update_platform(float time)
{
    /*
     aktualizacja platform
     */
    if(interaction_switched_)
    {
        if(!changed_arm_)
        {
            this->chagne_arm_interaction ();
        }
        this->move_platform (time);
    }
    if(moving_)
    {
        moving_side_to_side (time);
    }
}
void new_platform::render(sf::RenderWindow &window)
{
    window.draw (sprite_);
    if(this->interaction_)
    {
        window.draw (sprite_interaction_);
    }

}

sf::Sprite new_platform::return_sprite()
{
    return sprite_;
}

sf::Sprite new_platform::return_sprite_interaction()
{
    return sprite_interaction_;
}

