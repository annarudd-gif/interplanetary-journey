#include "Menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Screen.hpp"

Menu::Menu(sf::Font& font)
: startButton(font, "Start Game",{800.f,200.f}, 64),
      settingsButton(font, "Settings",{800.f,200.f}, 64){

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
        float centerX = win.getSize().x/2.f;
        float centerY = win.getSize().y/2.f;
        startButton.setButtonPosition(centerX,centerY-200.f);
        settingsButton.setButtonPosition(centerX,centerY+200.f);
        startButton.transformButton(win);
        settingsButton.transformButton(win);
    };

    void Menu::draw(sf::RenderWindow& win){
        startButton.drawButton(win);
        settingsButton.drawButton(win);
    };
