# pragma once
#include<SFML/Graphics.hpp>
#include<string>

struct Button{
    sf::RectangleShape background;
    sf::Text label;

    Button(sf::Font& font, const std::string& text,const sf::Vector2f pos, const sf::Vector2f size, int textSize);
    bool isMouseOver(const sf::Vector2f& mousePos)const;
    void setButtonPosition(float x, float y);
    void drawButton(sf::RenderWindow& win);
    void transformButton(sf::RenderWindow& win);


};