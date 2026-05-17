#include "Asteroid.hpp"
#include <SFML/Graphics.hpp>
#include <random>
    

Asteroid::Asteroid(const sf::Texture& asteroidTexture, sf::Vector2f pos,float radius,float speed,float rotation)
:asteroidSprite(asteroidTexture){
    this->radius=radius;
    this->speed=speed;
    hp=radius;
    

    //hitbox
    hitBox.setFillColor(sf::Color::Green);
    hitBox.setRadius(radius);
    hitBox.setOrigin({radius,radius});
    hitBox.setPosition(pos);

    float diameter=radius*2.f;

    //sprite
    asteroidSprite.setPosition(pos);
    asteroidSprite.setOrigin({asteroidTexture.getSize().x/2.f,asteroidTexture.getSize().y/2.f});
    asteroidSprite.setScale({diameter/asteroidTexture.getSize().x+0.05f,diameter/asteroidTexture.getSize().y+0.05f});
    asteroidSprite.setRotation(sf::degrees(rotation));

}



void Asteroid::draw(sf::RenderWindow& window){
    
    window.draw(asteroidSprite);
    
}
void Asteroid::update(float dt){
    if(hitCooldown>0.f){hitCooldown-=dt;}
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
float Asteroid::getCollisionDamage()const{
    return hp*0.5f;
}

 void Asteroid::takeDamage(float damage){
        hp-=damage;
        if(hp<0.f){hp=0.f;}
    }
bool Asteroid::isDead()const{
    return hp<=0.f;
}
bool Asteroid::canHit()const{
    return hitCooldown<=0.f;
}
void Asteroid::resetHitCooldown(){
    hitCooldown=2.f;
}
float Asteroid::getRotation()const{
    return asteroidSprite.getRotation().asDegrees();
}
sf::Vector2f Asteroid::getScale()const{
    return asteroidSprite.getScale();
}