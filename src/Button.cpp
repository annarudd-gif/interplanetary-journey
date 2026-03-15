#include "Button.hpp"

Button::Button(sf::Font& font, const std::string& text,float posX,float posY):label(font,text,64){
        float bgX=800.f;
        float bgY=200.f;

    background.setFillColor(sf::Color(255, 105, 180)); 
    background.setSize({bgX,bgY});
    background.setOrigin({bgX/2,bgY/2});   
    label.setFillColor(sf::Color::White);
    auto bounds=label.getLocalBounds();
    label.setOrigin({bounds.position.x+bounds.size.x / 2,
                     bounds.position.y+bounds.size.y / 2});
    background.setPosition({posX,posY});
    label.setPosition({posX,posY});
}
bool Button::isMouseOver(const sf::Vector2f& mousePos)const{
return background.getGlobalBounds().contains(mousePos);
}
void Button::setButtonPosition(float x, float y){
background.setPosition({x,y});
label.setPosition({x,y});
}
void Button::drawButton(sf::RenderWindow& win){
    win.draw(background);
    win.draw(label);
}
void Button::transformButton(sf::RenderWindow& win){
    sf::Vector2f mouseGloalPos=win.mapPixelToCoords(sf::Mouse::getPosition(win));
if(isMouseOver(mouseGloalPos)){
    background.setFillColor(sf::Color(255,140,200));
    background.setScale({1.05f,1.05f});
    label.setScale({1.05f,1.05f});
}
else{background.setFillColor(sf::Color(255, 105, 180));
    background.setScale({1.f,1.f});
    label.setScale({1.f,1.f});}

}
