#include "Button.hpp"

Button::Button(sf::Font& font, const std::string& text,const sf::Vector2f size, int textSize):label(font,text,textSize){
    background.setFillColor(sf::Color(255, 105, 180)); 
    background.setSize(size);
    background.setOrigin({size.x/2.f,size.y/2.f});   
    label.setFillColor(sf::Color::White);
    auto bounds=label.getLocalBounds();
    label.setOrigin({bounds.position.x+bounds.size.x / 2.f,
                     bounds.position.y+bounds.size.y / 2.f});
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


