#pragma once
#include "Config.hpp"
#include "SFML/Graphics.hpp"
#include "Screen.hpp"
#include "string"
#include <sstream>
#include <iomanip>
#include "Button.hpp"


enum class Category{
Rocket,
Asteroid
};




class Settings
{
private:
    bool settingsChanged = false;
    Config& config;
    sf::RenderWindow& win;
    sf::Font& font;
    Button saveButton;
    sf::Texture green;
    sf::Texture red;
    int selectedIndex = 0;

    struct SettingItem
{
    std::string name;
    sf::Text text;
    sf::Sprite box;
    sf::RectangleShape background;
    sf::Text valueText;
    Category type;
    float& oriiginalValue;
    float tempValue;
    bool modified=false;

    SettingItem(std::string name,float& value,sf::Texture& texture, sf::Font& font, sf::Vector2f size,Category type)
    :box(texture),text(font),valueText(font),oriiginalValue(value){
        tempValue=value;
        this->name=name;
        this->type=type;

        background.setSize(size);
        background.setFillColor(sf::Color(88, 24, 88));

        text.setString(name);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        std::stringstream ss;

    ss << std::fixed
    << std::setprecision(1)
    << tempValue;

        valueText.setString(ss.str());
        valueText.setCharacterSize(24);
        valueText.setFillColor(sf::Color::White);
        valueText.setOrigin({valueText.getLocalBounds().size.x/2.f,valueText.getLocalBounds().size.y/2.f});

        box.setOrigin({static_cast<float>(texture.getSize().x/2.f),static_cast<float>(texture.getSize().y/2.f)});
        box.setScale({0.15,0.12});



    }
      
};
std::vector<SettingItem> items;
public:
Settings(Config& config, sf::RenderWindow& win,sf::Font& font);
void init();
void handleInput(const sf::Event& event, Screen& currentScreen);
void update(float dt);
void draw();
void saveSettings();
bool getSettingsChanged();
void setSettingsChanged(bool b);

};


