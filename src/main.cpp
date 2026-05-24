#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <iostream>
#include "Screen.hpp"
#include "Game.hpp"
#include "Settings.hpp"
#include "Config.hpp"





/*загальна обробка подій*/
void processEvents(sf::RenderWindow& win,Screen& currentScreen,Menu& menu,Game& game,Settings& settings){
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
        settings.handleInput(*event,currentScreen);
    }
}


}

int main() /*самий початок, назва та версія гри*/{


    std::cout << "Interplanetary Journey" << std::endl;
   
    
/*Стан екрану*/
    Screen currentScreen=Screen::Menu;
/*Завантаження та перевірка шрифтів*/
    sf::Font font;
    if(!font.openFromFile("assets/fonts/Strogo-Regular.ttf")){
        std::cerr<<"Error loading font"<<std::endl;
    }
/*Створення головного вікна*/
    sf::RenderWindow mainWindow(sf::VideoMode({1920, 1080}), "Interplanetary Journey");
    mainWindow.setFramerateLimit(60);
    
 
/*основні змінні*/
    Config config;
    config.load();
    float winX=mainWindow.getSize().x;
    float winY=mainWindow.getSize().y;
    sf::Clock clock;
    float dt;
    Menu menu(font,winX);
    Game game (mainWindow, font,dt,config);
    Settings settings(config, mainWindow, font);
    
   

/*Головний цикл*/
    while (mainWindow.isOpen()) {
        dt=clock.restart().asSeconds();
        /*метод обробки подій*/
        processEvents(mainWindow,currentScreen,menu,game,settings);

 /*Налаштування позицій та малювання наповнення вікна для меню*/
if(currentScreen==Screen::Menu){
    mainWindow.setView(mainWindow.getDefaultView());
    menu.update(mainWindow);
    mainWindow.clear(sf::Color(10,20,50));
    menu.draw(mainWindow);
    mainWindow.display();}
/*Налаштування позицій та малювання наповнення вікна для гри*/
else if(currentScreen==Screen::Game){
    game.update();
    mainWindow.clear(sf::Color(10,20,50));
    game.draw();
    mainWindow.display();}
/*Налаштування позицій та малювання наповнення вікна для налаштувань*/
else if(currentScreen==Screen::Settings){
    if(settings.getSettingsChanged()){
        game.reloadConfig();
        settings.setSettingsChanged(false);
    }

    mainWindow.setView(mainWindow.getDefaultView());
    settings.update(dt);
    mainWindow.clear(sf::Color(50,20,50));
    settings.draw();
    mainWindow.display();}}
    return 0;
}
