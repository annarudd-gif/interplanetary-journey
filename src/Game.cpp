#include "Game.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <algorithm>

static std::mt19937 gen(std::random_device{}());

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
    if(!asteroidTexture.loadFromFile("assets/textures/asteroid.png")){
        std::cout<<"<Failed to load asteroid texture\n";

    }
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
    player.update(dt,window.getSize().y);

    spawnTimer+=dt;
    if(spawnTimer>= spawnDelay){
        spawnTimer-=spawnDelay;
        spawnAsteroid(20.f,50.f);
        std::cout<<"spawned\n";

    }
        sf::Vector2f A=player.getRocketPoint(0);
        sf::Vector2f B=player.getRocketPoint(1);
        sf::Vector2f C=player.getRocketPoint(2);
    for(auto& asteroid: asteroids){
        asteroid.update(dt);

        sf::Vector2f center=asteroid.getPosition();
        float radius=asteroid.getRadius();
        

        if(circleTriangleCollision(center,radius,A,B,C)){std::cout<<"hit"<<std::endl;}
    }
    

    asteroids.erase(std::remove_if(asteroids.begin(),asteroids.end(),[](Asteroid& a){
        return a.isOffScreen();
    }),asteroids.end());

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
    for(auto& asteroid:asteroids){
        asteroid.draw(window);
    }
    window.setView(window.getDefaultView());
    window.draw(rocketHud.speedText);
    window.draw(rocketHud.engineText);
    window.draw(rocketHud.barBackground);
    window.draw(rocketHud.barFill);
}

void Game::initShader()
{
    if(!starShader.loadFromFile("assets/shaders/stars.frag", sf::Shader::Type::Fragment))
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

void Game::spawnAsteroid(float minR, float maxR){
    float rightEdge = camera.getCenter().x + camera.getSize().x / 2.f;
    float x = rightEdge + 100.f;

    std::uniform_real_distribution<float> distY(-50.f,window.getSize().y+50.f);
    float y= distY(gen);

    std::uniform_real_distribution<float> rotDist(0.f, 360.f);
    float rotation = rotDist(gen);
   
    std::uniform_real_distribution <float> radDist(minR,maxR);
    float radius = radDist(gen);
    
    std::uniform_real_distribution <float> spDist(-20.f,20.f);
    float speed = 10000.f / (radius * 0.5f + 1.f) + spDist(gen);

    asteroids.emplace_back(asteroidTexture,sf::Vector2f({x,y}),radius,speed,rotation);
}

bool Game::circleSegmentCollision(const sf::Vector2f& center,float radius, const sf::Vector2f& A, const sf::Vector2f& B){
    sf::Vector2f AB=B-A;
    sf::Vector2f ACenter= center-A;
    float dot = ACenter.x * AB.x + ACenter.y * AB.y;
    float abSq = AB.x * AB.x + AB.y * AB.y;
    if (abSq == 0.f)
    return false;

float t = dot / abSq;
    t=std::clamp(t,0.f,1.f);
    sf::Vector2f closest=A+t*AB;
    sf::Vector2f diff= center-closest;
    float distSq=diff.x*diff.x+diff.y*diff.y;

    return distSq<radius*radius;
}
bool Game::pointInTriangle(const sf::Vector2f& center,
                                const sf::Vector2f& A,
                                const sf::Vector2f& B,
                                const sf::Vector2f& C){
    float d1=sign(center,A,B);
    float d2=sign(center,B,C);
    float d3=sign(center,C,A);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}
float Game::sign(const sf::Vector2f& p1,const sf::Vector2f& p2,const sf::Vector2f& p3){
    return (p1.x - p3.x) * (p2.y - p3.y) -(p2.x - p3.x) * (p1.y - p3.y);
}

bool Game::circleTriangleCollision(const sf::Vector2f& center, float radius,
                                const sf::Vector2f& A,
                                const sf::Vector2f& B,
                                const sf::Vector2f& C){
if(circleSegmentCollision(center,radius,A,B))return true;
if(circleSegmentCollision(center,radius,B,C))return true;
if(circleSegmentCollision(center,radius,C,A))return true;
if(pointInTriangle(center,A,B,C))return true;
return false;}
