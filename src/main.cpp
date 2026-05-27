#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <iostream>
#include "Screen.hpp"
#include "Game.hpp"
#include "Settings.hpp"
#include "Config.hpp"





/*загальна обробка подій*/
void processEvents(sf::RenderWindow& win,Screen& currentScreen,Menu& menu,Game& game,Settings& settings,bool& fullScreen){
/*Цикл обробки подій */
while (const auto event = win.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
        win.close();
        break;
    }
     if(const auto* keyPressed=event->getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::F11){
            fullScreen=!fullScreen;

            if(fullScreen){
                win.create(sf::VideoMode::getDesktopMode(),"Interplanetary Journey",sf::State::Fullscreen);
                win.setView(win.getDefaultView());
                win.setFramerateLimit(60);

            }
            else{win.create(
            sf::VideoMode({1920,1080}),"Interplanetary Journey",sf::Style::Titlebar | sf::Style::Close);
            win.setView(win.getDefaultView());
            win.setFramerateLimit(60);}
        }

     }

    if(currentScreen==Screen::Menu){
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
    Screen previousScreen = currentScreen;
    bool fullScreen=false;

  
/*Створення головного вікна*/
    sf::RenderWindow mainWindow(sf::VideoMode({1920, 1080}), "Interplanetary Journey",sf::Style::Titlebar | sf::Style::Close);

     sf::View cameraUi;

      cameraUi.setSize({1920.f,1080.f});
    cameraUi.setCenter({960.f,540.f});

/*Завантаження та перевірка шрифтів*/
    sf::Font font;
    if(!font.openFromFile("assets/fonts/Strogo-Regular.ttf")){
        std::cerr<<"Error loading font"<<std::endl;
    }

    
 
/*основні змінні*/
    Config config;
    config.load();
    sf::Clock clock;
    float dt;
    Menu menu(font);
    Game game (mainWindow, font,dt,config,cameraUi);
    Settings settings(config, mainWindow, font,cameraUi);
    
   

/*Головний цикл*/
    while (mainWindow.isOpen()) {
        dt=clock.restart().asSeconds();
        /*метод обробки подій*/
        processEvents(mainWindow,currentScreen,menu,game,settings,fullScreen);

 /*Налаштування позицій та малювання наповнення вікна для меню*/
if(currentScreen==Screen::Menu){
    mainWindow.setView(mainWindow.getDefaultView());
    menu.update(mainWindow);
    mainWindow.clear(sf::Color(10,20,50));
    menu.draw(mainWindow);
    mainWindow.display();}
/*Налаштування позицій та малювання наповнення вікна для гри*/
else if(currentScreen==Screen::Game){

    if(currentScreen == Screen::Game &&
   previousScreen != Screen::Game)
{
    game.reStart();
}

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
    mainWindow.display();}

    previousScreen = currentScreen;}
    return 0;
}
