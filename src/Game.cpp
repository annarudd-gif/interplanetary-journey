#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen.hpp"
#include "Rocket.hpp"

Game::Game(float winX,float winY):player(winX/2,winY/2), camera(), winY(winY){   
    camera.setSize({winX,winY});
    camera.setCenter({winX/2,winY/2});

}
void Game::handleInput(const sf::Event& event,Screen& currentScreen){
        if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
            if(keyPressed->code==sf::Keyboard::Key::Escape){
                currentScreen=Screen::Menu;
            }
            if(keyPressed->code==sf::Keyboard::Key::W||keyPressed->code==sf::Keyboard::Key::Up){
                player.Up=true;
            }
            if(keyPressed->code==sf::Keyboard::Key::S||keyPressed->code==sf::Keyboard::Key::Down){
                player.Down=true;
            }
            if(keyPressed->code==sf::Keyboard::Key::D||keyPressed->code==sf::Keyboard::Key::Right){
                player.Right=true;
            }
        }

        if(const auto* KeyReleased=event.getIf<sf::Event::KeyReleased>()){
            if(KeyReleased->code==sf::Keyboard::Key::W||KeyReleased->code==sf::Keyboard::Key::Up){
                player.Up=false;
            }
            if(KeyReleased->code==sf::Keyboard::Key::S||KeyReleased->code==sf::Keyboard::Key::Down){
                player.Down=false;
            }
            if(KeyReleased->code==sf::Keyboard::Key::D||KeyReleased->code==sf::Keyboard::Key::Right){
                player.Right=false;
            }
        }
}
void Game::update(float dt){
    player.update(dt);
    camera.setCenter({player.getPosition().x,winY/2.f});
}
void Game::draw(sf::RenderWindow& win){
    win.setView(camera);
    player.draw(win);
   
}