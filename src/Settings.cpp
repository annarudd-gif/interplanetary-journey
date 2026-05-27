#include "Config.hpp"
#include "SFML/Graphics.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "iostream"
#include "algorithm"
#include "Button.hpp"

/*обробка подій налаштувань*/
    void Settings::handleInput(const sf::Event& event, Screen& currentScreen){
        if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
            if(keyPressed->code==sf::Keyboard::Key::Escape){
                currentScreen=Screen::Menu;
            }
            if(keyPressed->code==sf::Keyboard::Key::Down){
                selectedIndex++;
            }
            if(keyPressed->code==sf::Keyboard::Key::Up){
                selectedIndex--;
            }
            selectedIndex=std::clamp(selectedIndex,0,(int)items.size()-1);

            if(keyPressed->code==sf::Keyboard::Key::Right){
                items[selectedIndex].tempValue+=0.1f;
            }
            if(keyPressed->code==sf::Keyboard::Key::Left){
                items[selectedIndex].tempValue-=0.1f;
            }
            if(items[selectedIndex].tempValue<0){
                items[selectedIndex].tempValue=0.f;
            }

            std::stringstream ss;

ss << std::fixed
   << std::setprecision(1)
   << items[selectedIndex].tempValue;

items[selectedIndex].valueText.setString(ss.str());

        }
        if(const auto* mousePressed=event.getIf<sf::Event::MouseButtonPressed>()){
            if(mousePressed->button == sf::Mouse::Button::Left){
                sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));

                if(saveButton.isMouseOver(mousePos)){
                    saveSettings();
                }
            }
        }
    };

    Settings::Settings(Config& config, sf::RenderWindow& win,sf::Font& font,sf::View& cameraUi):config(config),win(win),font(font),
    saveButton(font,"Save",{300.f,100.f},32), cameraUi(cameraUi){

        if(!green.loadFromFile("assets/textures/green_box.png")){
        std::cout<<"<Failed to load green_box texture\n";
        }
         if(!red.loadFromFile("assets/textures/red_box.png")){
        std::cout<<"<Failed to load red_box texture\n";
        }

        init();
        saveButton.setButtonPosition(win.getSize().x-170.f,win.getSize().y-70.f);

    }

    void Settings::init()
{
    float leftY = 50.f;
    float rightY = 50.f;
    float rightX=win.getSize().x/2.f;

    items.emplace_back("Base Speed:",config.baseSpeed, green, font, sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Timer CoolDown:",config.timerCoolDown,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Boost Duration:",config.boostDuration,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Overheart Speed Drop:",config.overheatSpeedDrop,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Base Speed Decay:",config.baseSpeedDecay,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Boost Build Rate:",config.boostBuildRate,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Boost Max:",config.boostMax,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Boost Decay:",config.boostDecay,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Hp Max:",config.hpMax,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);
    items.emplace_back("Rotation Speed:",config.rotationSpeed,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Rocket);

    items.emplace_back("Spawn Delay:",config.spawnDelay,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Asteroid);
    items.emplace_back("Min Asteroid Radius:",config.minAstRadius,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Asteroid);
    items.emplace_back("Max Asteroid Radius:",config.maxAstRadius,green,font,sf::Vector2f(win.getSize().x / 2.f,80.f),Category::Asteroid);

    float sizeY = items[0].background.getSize().y;

    for(auto& item : items)
    {
        if(item.type==Category::Rocket){
        item.background.setPosition({0.f, leftY});

        item.text.setPosition({20.f,leftY + 20.f});

        item.box.setPosition({
            item.background.getPosition().x + item.background.getSize().x - 106.f,leftY+40.f});
        item.valueText.setPosition({item.box.getPosition().x,item.box.getPosition().y-6.f});

        leftY += sizeY + 20.f;
    }
    else{
        item.background.setPosition({rightX, rightY});

        item.text.setPosition({rightX+20.f,rightY + 20.f});

        item.box.setPosition({
            item.background.getPosition().x +
            item.background.getSize().x - 106.f,rightY+40.f});
        item.valueText.setPosition(item.box.getPosition());

        rightY += sizeY + 20.f;

    }}


}

void Settings::update(float dt){
    
    for(size_t i=0; i<items.size(); i++){
        if(items[i].tempValue != items[i].oriiginalValue)
        {items[i].box.setTexture(red);
        items[i].modified=true;}
        else{ items[i].box.setTexture(green);}

    }
    saveButton.transformButton(win);
}

void Settings::draw()
{
    
    win.setView(cameraUi);
    for(size_t i = 0; i < items.size(); i++)
    {
        
      if(i==selectedIndex){win.draw(items[i].background);}

        win.draw(items[i].box);
        win.draw(items[i].valueText);

        win.draw(items[i].text);
    }
    saveButton.drawButton(win);
}

void Settings::saveSettings(){
    for(size_t i=0; i < items.size(); i++){
        items[i].oriiginalValue=items[i].tempValue;
        items[i].modified=false;
        items[i].box.setTexture(green);
        

    }
    config.save();
    settingsChanged=true;
}

bool Settings::getSettingsChanged(){
    return settingsChanged;
}

void Settings::setSettingsChanged(bool b){
    settingsChanged=b;

}

    


