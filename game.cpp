#include "game.h"
#include <iostream>
Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->collision_ = new collision;
    this->platform_ = new platform(this->collision_);
    this->player_ = new player(this->collision_);

    this->initVariables();

}

Game::~Game()
{

}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 900), "Sword and hammer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
    this->collision_->copy_platforms (this->platform_->return_sprites ());
    this->hero_x_position_=0;
}

void Game::updatePollEvents()
{
    sf::Event e;

    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
        {
            this->window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }

    }
}

void Game::update()
{
    this->clock_.restart ();

    this->updatePollEvents();

    this->hero_x_position_=this->player_->return_hero_x_position ();

    this->background_->update_background (hero_x_position_);

    this->platform_->update_platforms (hero_x_position_);

    this->collision_->copy_platforms (this->platform_->return_sprites ());

    this->player_->update_hero();

}

void Game::gamerender()
{
    this->window->clear ();

    this->background_->render (*this->window);

    this->platform_->render (*this->window);

    this->player_->render (*this->window);

    this->window->display();
}

bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

