#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <iostream>
#include "Screen.hpp"
#include "Game.hpp"


/*обробка подій налаштувань*/
    void handleSettingsInput(const sf::Event& event, Screen& currentScreen){
        if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
            if(keyPressed->code==sf::Keyboard::Key::Escape){
                currentScreen=Screen::Menu;
            }
        }
    };


/*загальна обробка подій*/
void processEvents(sf::RenderWindow& win,Screen& currentScreen,Menu& menu,Game& game){
/*Цикл обробки подій */
while (const auto event = win.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
        win.close();
        break;
    }

    else if(currentScreen==Screen::Menu){
        menu.handleInput(*event,win, currentScreen);      
    }

    else if(currentScreen==Screen::Game){
        game.handleInput(*event,currentScreen);
    }

    else if(currentScreen==Screen::Settings){
        handleSettingsInput(*event,currentScreen);
    }
}


}

int main() /*самий початок, назва та версія гри*/{
    std::cout << "Interplanetary Journey v2.0.0" << std::endl;
    
/*Стан екрану*/
    Screen currentScreen=Screen::Menu;
/*Завантаження та перевірка шрифтів*/
    sf::Font font;
    if(!font.openFromFile("project/assets/fonts/Strogo-Regular.ttf")){
        std::cerr<<"Error loading font"<<std::endl;
    }
/*Створення головного вікна*/
    sf::RenderWindow mainWindow(sf::VideoMode({1920, 1080}), "Interplanetary Journey");
    mainWindow.setFramerateLimit(60);
    
 
/*основні змінні*/
    float winX=mainWindow.getSize().x;
    float winY=mainWindow.getSize().y;
    sf::Clock clock;
    float dt;
    Menu menu(font,winX);
    Game game (winX,winY);
    
   

/*Головний цикл*/
    while (mainWindow.isOpen()) {
        dt=clock.restart().asSeconds();
        /*метод обробки подій*/
        processEvents(mainWindow,currentScreen,menu,game);

 /*Налаштування позицій та малювання наповнення вікна для меню*/
if(currentScreen==Screen::Menu){
    mainWindow.setView(mainWindow.getDefaultView());
    menu.update(mainWindow);
    mainWindow.clear(sf::Color(10,20,50));
    menu.draw(mainWindow);
    mainWindow.display();}
/*Налаштування позицій та малювання наповнення вікна для гри*/
else if(currentScreen==Screen::Game){
    game.update(dt);
    mainWindow.clear(sf::Color(10,20,50));
    game.draw(mainWindow);
    mainWindow.display();}
/*Налаштування позицій та малювання наповнення вікна для налаштувань*/
else if(currentScreen==Screen::Settings){
    mainWindow.setView(mainWindow.getDefaultView());
    mainWindow.clear(sf::Color(50,20,50));
    mainWindow.display();}}
    return 0;
}
