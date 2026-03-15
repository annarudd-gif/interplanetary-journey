# pragma once
# include<SFML/Graphics.hpp>
# include "Button.hpp"
#include "Screen.hpp"

class Menu
{
private:
    Button startButton;
    Button settingsButton;
public:
Menu(sf::Font& font, float winX);
    void handleInput(const sf::Event& event,sf::RenderWindow& win, Screen& currentScreen);
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);
};
