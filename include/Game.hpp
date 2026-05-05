#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Rocket.hpp"
#include <string>
#include "Asteroid.hpp"



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

class Game {
private:
    std::vector<Asteroid> asteroids;
    float time;
    float& dt;
    sf::Font& font;
    sf::RenderWindow& window;
    RocketStats rocketStats;
    RocketHud rocketHud;
    sf::Shader starShader;
    sf::RectangleShape backgroundQuad;
    sf::Clock shaderClock;
    sf::Texture asteroidTexture;
    float spawnTimer = 0.f;
    float spawnDelay = 2.f;
   
    float k;

    Rocket player;
    sf::View camera;

public:
    Game(sf::RenderWindow& window, sf::Font& font, float& dtRef);
    void initShader();
    void initHud();
    void initStats();
    void handleInput(const sf::Event& event, Screen& currentScreen);
    void update();
    void draw();
    void updateTime();
    void updateHud();
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
};

