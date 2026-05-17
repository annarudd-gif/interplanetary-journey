#pragma once
#include "SFML/Graphics.hpp"

class Explosion{
    private:
    sf::Sprite sprite;
    sf::Vector2i frameSize;
    int frameCount;
    int currentFrame=0;
    float frameTime;
    float elapsedTime;
    bool finished=false;
    public:
    Explosion(const sf::Texture& texture,
         float frameTime,
         const sf::Vector2f& position,
          float rotation,
          const sf::Vector2f scale,sf::Vector2i frameSize);
    void draw(sf::RenderWindow& win)const;
    void update(float dt);
    void nextFrame();
    bool isFinished()const;



};