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
    float hitCooldown=0.f;

public:
    Asteroid(const sf::Texture& asteroidTexture, sf::Vector2f pos,float radius,float speed, float rotation);
   
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen();
    sf::Vector2f getPosition()const;
    float getRotation()const;
    sf::Vector2f getScale()const;
    float getRadius()const;
    float getCollisionDamage()const;
    void takeDamage(float damage);
    bool isDead()const;
    bool canHit()const;
    void resetHitCooldown();
};




