#include "Game.hpp"
#include <cmath>
#include <iostream>

RocketHud::RocketHud(sf::Font& font)
    : speedText(font), engineText(font)   // создаем тексты сразу с font
{
    speedText.setCharacterSize(24);
    speedText.setFillColor(sf::Color::White);
    speedText.setString("rocket speed: 0");

    engineText.setCharacterSize(24);
    engineText.setFillColor(sf::Color::White);
    engineText.setString("Engine: READY");

    barBackground.setSize({200.f, 16.f});
    barBackground.setFillColor(sf::Color(60, 60, 60));

    barFill.setSize({0.f, 16.f});
    barFill.setFillColor(sf::Color::White);
}

// ---------------- Game -----------------

Game::Game(sf::RenderWindow& window, sf::Font& font, float& dtRef)
    : dt(dtRef),font(font), window(window), rocketStats(), rocketHud(font), player(window.getSize().x, window.getSize().y),
      camera()
{
    time = 0.f;
    camera.setSize({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    camera.setCenter({static_cast<float>(window.getSize().x)/2.f, static_cast<float>(window.getSize().y)/2.f});

    initShader();
    initStats();
    initHud();
}
void Game::handleInput(const sf::Event& event,Screen& currentScreen){ 
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){ 
        if(keyPressed->code==sf::Keyboard::Key::Escape){ currentScreen=Screen::Menu; } 
        if(keyPressed->code==sf::Keyboard::Key::W||keyPressed->code==sf::Keyboard::Key::Up){ player.Up=true; } 
        if(keyPressed->code==sf::Keyboard::Key::S||keyPressed->code==sf::Keyboard::Key::Down){ player.Down=true; } 
        if(keyPressed->code==sf::Keyboard::Key::D||keyPressed->code==sf::Keyboard::Key::Right){ player.Right=true; } } 
        if(const auto* KeyReleased=event.getIf<sf::Event::KeyReleased>()){ 
            if(KeyReleased->code==sf::Keyboard::Key::W||KeyReleased->code==sf::Keyboard::Key::Up){ player.Up=false; } 
            if(KeyReleased->code==sf::Keyboard::Key::S||KeyReleased->code==sf::Keyboard::Key::Down){ player.Down=false; } 
            if(KeyReleased->code==sf::Keyboard::Key::D||KeyReleased->code==sf::Keyboard::Key::Right){ player.Right=false; } } 
        }

void Game::update()
{
    player.update(dt);
    camera.setCenter({player.getPosition().x, window.getSize().y / 2.f});
    updateTime();
    updateHud();
}

void Game::draw()
{
    float t = shaderClock.getElapsedTime().asSeconds();
    starShader.setUniform("u_time", t);
    starShader.setUniform("u_resolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));
    starShader.setUniform("offset", sf::Glsl::Vec2(player.getPosition().x, 0.f));

    window.setView(window.getDefaultView());
    window.draw(backgroundQuad, &starShader);

    window.setView(camera);
    player.draw(window);
    window.setView(window.getDefaultView());
    window.draw(rocketHud.speedText);
    window.draw(rocketHud.engineText);
    window.draw(rocketHud.barBackground);
    window.draw(rocketHud.barFill);
}

void Game::initShader()
{
    if(!starShader.loadFromFile("project/assets/shaders/stars.frag", sf::Shader::Type::Fragment))
        std::cerr << "Failed to load shader\n";
    backgroundQuad.setSize({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    backgroundQuad.setPosition({0.f, 0.f});
}

void Game::initStats()
{
    rocketStats.speed = player.getSpeed();
    rocketStats.engineState = player.getEngineCondition();
    rocketStats.barWidth = 200.f;
    rocketStats.boostRatio = player.currentBoost / k;
}

void Game::initHud()
{
    float margin = 20.f;
    rocketHud.speedText.setPosition({static_cast<float>(window.getSize().x)-280.f, margin});
    rocketHud.engineText.setPosition({static_cast<float>(window.getSize().x)-280.f, margin+35.f});
    rocketHud.barBackground.setPosition({static_cast<float>(window.getSize().x)-280.f, margin+75.f});
    rocketHud.barFill.setPosition({static_cast<float>(window.getSize().x)-280.f, margin+75.f});
}

void Game::updateTime()
{
    if(time < 1.f)
        time += dt;
    else {
        time = 0.f;
        rocketStats.speed = player.getSpeed();
        rocketStats.engineState = player.getEngineCondition();
    }
    k = player.boostMax / rocketStats.barWidth;
    rocketStats.boostRatio = player.currentBoost / k;
}

void Game::updateHud()
{
    rocketHud.speedText.setString("rocket speed: " + std::to_string(static_cast<int>(rocketStats.speed)));
    rocketHud.engineText.setString("Engine: " + rocketStats.engineState);
    rocketHud.barFill.setSize({static_cast<float>(std::round(rocketStats.boostRatio)), 16.f});
}
