#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<optional>

enum class StatusEngine{
Normal,
Boosting,
MaxSpeed,
Cooling,
Cooldown
};


struct Rocket{
    sf::Texture rocketTexture;
    sf::Texture rocketFlamesTexture;
    std::optional<sf::Sprite> rocketSprite;
    StatusEngine status;
    StatusEngine lastStatus;
    sf::Vector2f direction;
    const float timerCoolDown=20.f;
    const float boostDuration=5.f;
    const float overheatSpeedDrop=40.f;
    const float baseSpeedDecay=20.f;
    float rocketCenterOffset;
    float elapsedTime;
    float overheatTime;
    float totalSpeed;
    float boostBuildRate;
    float currentBoost;
    float baseSpeed;
    float boostMax;
    float boostDecay;
    bool canBoost;
    bool Up;
    bool Down;
    bool Right;
    float angle;
    float rotationSpeed;
    float hp;
    float hpMax;
    float collisionDamage=5.f;
    sf::ConvexShape rocket;
    Rocket(float startX, float startY);
    void draw(sf::RenderWindow& win);
    float rad(float angle);
    void update(float dt, float worldHeight);
    std::string getEngineCondition();
    sf::Vector2f getPosition();
    float getSpeed();
    bool hasCooldownExpired(float& dt);
    bool updateOverheatTimer(float& dt);
    sf::Vector2f getRocketPoint(int num);
    void takeDamage(float damage);
    float getCollisionDamage()const;
    bool isDead()const;
    float getHpMax()const;
    float getHp()const;

  
};
