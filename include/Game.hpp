#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "Rocket.hpp"
#include <string>

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
    float time;
    float& dt;
    sf::Font& font;
    sf::RenderWindow& window;
    RocketStats rocketStats;
    RocketHud rocketHud;
    sf::Shader starShader;
    sf::RectangleShape backgroundQuad;
    sf::Clock shaderClock;
   
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
};