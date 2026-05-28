# pragma once
#include<SFML/Graphics.hpp>
#include<string>


struct Button{
    sf::RectangleShape background;
    sf::Text label;

    Button(sf::Font& font, const std::string& text,const sf::Vector2f size, int textSize);
    bool isMouseOver(const sf::Vector2f& mousePos)const;
    void setButtonPosition(float x, float y);
    void drawButton(sf::RenderWindow& win);
    void transformButton(sf::RenderWindow& win);
    


};

struct IconButton
{
    sf::Sprite spriteIconButton;
    

    IconButton(sf::Texture& tex, float scale);

    bool isMouseOver(const sf::Vector2f& mousePos)const;
    void setButtonPosition(float x, float y);
    void drawButton(sf::RenderWindow& win);
    void transformButton(sf::RenderWindow& win);
    void setTexture(const sf::Texture& tex );
    void setPosition(sf::Vector2f pos);
   
};
