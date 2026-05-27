#include "Explosion.hpp"
#include "SFML/Graphics.hpp"



    
Explosion::Explosion(const sf::Texture& texture,
     float frameTime
     ,const sf::Vector2f& position
     , float rotation
     ,const sf::Vector2f scale,sf::Vector2i frameSize)
:sprite(texture)
{
this->frameSize=frameSize;
frameCount=texture.getSize().x/frameSize.x;
this->frameTime=frameTime;
sprite.setTextureRect(sf::IntRect({0,0},frameSize));
sprite.setOrigin(
{
    frameSize.x / 2.f,
    frameSize.y / 2.f
});
sprite.setRotation(sf::degrees(rotation));
sprite.setScale(scale);
sprite.setPosition(position);
}

void Explosion::update(float dt){
 elapsedTime+=dt;
 if(elapsedTime>=frameTime){
    elapsedTime=0.f;
    nextFrame();

 }
}

void Explosion::nextFrame(){
    currentFrame++;
    if(currentFrame>=frameCount){
        finished=true;
        return;
        
    }
        sprite.setTextureRect(
            sf::IntRect({currentFrame*frameSize.x,0}
            ,frameSize));

}

void Explosion::draw(sf::RenderWindow& win)const{
    win.draw(sprite);
}
bool Explosion::isFinished()const{
    return finished;
}



 