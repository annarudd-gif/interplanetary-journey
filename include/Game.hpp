# pragma once
# include<SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Rocket.hpp"

class Game
{
private:
Rocket player;
sf::View camera;
float winY;
public:
Game(float winX,float winY);
void handleInput(const sf::Event& event,Screen& currentScreen);
void update(float dt);
void draw(sf::RenderWindow& win);
   
};


