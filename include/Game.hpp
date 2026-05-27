#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Rocket.hpp"
#include <string>
#include "Asteroid.hpp"
#include "Explosion.hpp"
#include "Config.hpp"



struct RocketStats {
    float speed;
    std::string engineState;
    float boostRatio;
    float barWidth;
};

struct RocketHud {
    sf::Text speedText;
    sf::Text engineText;
    sf::RectangleShape barBackground;
    sf::RectangleShape barFill;

    RocketHud(sf::Font& font); // конструктор с font
};

struct HPRocket{
    sf::Text hp;
    sf::RectangleShape barBackground;
    sf::RectangleShape barFill;

    HPRocket(sf::Font& font);
};

class Game {
private:
    Config& config;
    std::vector<Asteroid> asteroids;
    std::vector<Explosion> explosions;
    bool deathHandled=false;
    float time;
    float& dt;
    sf::Font& font;
    sf::RenderWindow& window;
    RocketStats rocketStats;
    RocketHud rocketHud;
    HPRocket hpRocket;
    sf::Shader starShader;
    sf::RectangleShape backgroundQuad;
    sf::Clock shaderClock;
    sf::Texture asteroidTexture;
    sf::Texture asteroid_sprite_sheet;
    sf::Texture rocket_sprite_sheet;
    float spawnTimer = 0.f;
   
   
    float k;

    Rocket player;
    sf::View camera;
     sf::View& cameraUi;
   

public:
    Game(sf::RenderWindow& window, sf::Font& font, float& dtRef,Config& config, sf::View& cameraUi);
    void initShader();
    void setPositionHud();
    void initStats();
    void setPositionHPRocket();
    void handleInput(const sf::Event& event, Screen& currentScreen);
    void update();
    void draw();
    void reloadConfig();
    void updateTime();
    void updateHud();
    void updateHPRocket();
    void spawnAsteroid(float minR, float maxR);
    bool circleSegmentCollision(const sf::Vector2f& center,float radius, const sf::Vector2f& A, const sf::Vector2f& B);
    bool circleTriangleCollision(const sf::Vector2f& center, float radius,
                                const sf::Vector2f& A,
                                const sf::Vector2f& B,
                                const sf::Vector2f& C);
    bool pointInTriangle(const sf::Vector2f& center,
                                const sf::Vector2f& A,
                                const sf::Vector2f& B,
                                const sf::Vector2f& C);
    float sign(const sf::Vector2f& p1,const sf::Vector2f& p2,const sf::Vector2f& p3);
    void reStart();
    
};

