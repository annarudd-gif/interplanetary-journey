#include "Asteroid.hpp"
#include <SFML/Graphics.hpp>
#include <random>
    

Asteroid::Asteroid(const sf::Texture& asteroidTexture, sf::Vector2f pos,float radius,float speed,float rotation)
:asteroidSprite(asteroidTexture){
    this->radius=radius;
    this->speed=speed;
    

    //hitbox
    hitBox.setFillColor(sf::Color::Green);
    hitBox.setRadius(radius);
    hitBox.setOrigin({radius,radius});
    hitBox.setPosition(pos);

    float diameter=radius*2.f;

    //sprite
    asteroidSprite.setPosition(pos);
    asteroidSprite.setOrigin({asteroidTexture.getSize().x/2.f,asteroidTexture.getSize().y/2.f});
    asteroidSprite.setScale({diameter/asteroidTexture.getSize().x+0.1f,diameter/asteroidTexture.getSize().y+0.1f});
    asteroidSprite.setRotation(sf::degrees(rotation));

}



void Asteroid::draw(sf::RenderWindow& window){
    window.draw(hitBox);
    window.draw(asteroidSprite);
    
}
void Asteroid::update(float dt){
    hitBox.move({-speed*dt,0.f});
    asteroidSprite.setPosition(hitBox.getPosition());
}

bool Asteroid::isOffScreen(){
    return hitBox.getPosition().x<-100.f;
}
sf::Vector2f Asteroid::getPosition() const{
    return hitBox.getPosition();
}
float Asteroid::getRadius()const{
    return hitBox.getRadius();
}