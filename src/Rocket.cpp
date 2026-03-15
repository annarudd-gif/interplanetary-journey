# include "Rocket.hpp"


  
      
    Rocket::Rocket(float startX, float startY){
        X=startX;
        Y=startY;
        baseSpeed=300.f;
        thrustSpeed=200.f;
        Up=false;
        Down=false;
        Right=false;
        rocket.setPointCount(3);
        rocket.setFillColor(sf::Color::Yellow);
        rocket.setPoint(0,sf::Vector2f(0.f,-40.f));
        rocket.setPoint(1,sf::Vector2f(-20.f,20.f));
        rocket.setPoint(2,sf::Vector2f(20.f,20.f));
        rocket.setOrigin({10.f,0.f});
        rocket.setRotation(sf::degrees(90.f));
        rocket.setPosition({startX,startY});
    }
    void Rocket::draw(sf::RenderWindow& win){
        win.draw(rocket);
    }
    void Rocket::update(float dt){
        if(Up){
            rocket.move({0.f,-baseSpeed*dt});
        }
        if (Down){
            rocket.move({0.f,+baseSpeed*dt});
        }
        if (Right){
           rocket.move({(+thrustSpeed+baseSpeed)*dt,0.f});
        }
        else{rocket.move({+baseSpeed*dt,0.f});}
            
    }
    sf::Vector2f Rocket::getPosition(){
        return sf::Vector2f{rocket.getPosition().x,rocket.getPosition().y};
    }
    
        
    
   


