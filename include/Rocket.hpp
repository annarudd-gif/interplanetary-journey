#pragma once
#include<SFML/Graphics.hpp>




struct Rocket{
    float X;
    float Y;
    float baseSpeed;
    float thrustSpeed;
    bool Up;
    bool Down;
    bool Right;
    sf::ConvexShape rocket;
    Rocket(float startX, float startY);
    void draw(sf::RenderWindow& win);
    void update(float dt);
    sf::Vector2f getPosition();

  
};
