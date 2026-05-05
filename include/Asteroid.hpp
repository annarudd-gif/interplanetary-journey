#pragma once
#include <SFML/Graphics.hpp>

class Asteroid
{
private:
    sf::CircleShape hitBox;
    sf::Sprite asteroidSprite;
    float speed;
    float radius;
    float hp;

public:
    Asteroid(const sf::Texture& asteroidTexture, sf::Vector2f pos,float radius,float speed, float rotation);
   
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen();
    sf::Vector2f getPosition()const;
    float getRadius()const;
};




