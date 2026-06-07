# pragma once
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "Button.hpp"
# include "Screen.hpp"
# include <optional>

class Menu
{
private:
    Button startButton;
    Button settingsButton;

    sf::SoundBuffer buttonBuffer;
    std::optional<sf::Sound> buttonSound;

public:
Menu(sf::Font& font);
    void handleInput(const sf::Event& event,sf::RenderWindow& win, Screen& currentScreen);
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);
};
