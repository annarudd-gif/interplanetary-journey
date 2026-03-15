#include "Menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen.hpp"

Menu::Menu(sf::Font& font, float winX )
: startButton(font, "Start Game", winX/ 2.f, 300.f),
      settingsButton(font, "Settings", winX/ 2.f, 600.f){

}


/*обробка подій меню*/
    void Menu::handleInput(const sf::Event& event,sf::RenderWindow& win, Screen& currentScreen){ 
        if(const auto* mousePressed=event.getIf<sf::Event::MouseButtonPressed>()){
            if(mousePressed->button==sf::Mouse::Button::Left){
                sf::Vector2f mousePos=win.mapPixelToCoords(mousePressed->position);
                if(startButton.isMouseOver(mousePos)){
                    std::cout<<"Start button clicked"<<std::endl;
                    currentScreen=Screen::Game;
                }
                else if(settingsButton.isMouseOver(mousePos)){
                    std::cout<<"Settings button clicked"<<std::endl;
                    currentScreen=Screen::Settings;
                }
            }

        }
    };
/*перевірка наведення миші на кнопки*/
    void Menu::update(sf::RenderWindow& win){
        startButton.transformButton(win);
        settingsButton.transformButton(win);
    };

    void Menu::draw(sf::RenderWindow& win){
        startButton.drawButton(win);
        settingsButton.drawButton(win);
    };
