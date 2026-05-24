# include "Rocket.hpp"
#include "cmath"
#include <iostream>
#include "Config.hpp"
  
      
    Rocket::Rocket(float startX, float startY,Config& config):config(config){
        reloadConfig();

        if(!rocketTexture.loadFromFile("assets/textures/rocket.png")){
            std::cout<<"<Failed to load rocket texture\n";
        }
        if(!rocketFlamesTexture.loadFromFile("assets/textures/rocketWithFlames.png")){
            std::cout<<"<Failed to load rocketWithFlames texture\n";
        }
        rocketSprite.emplace(rocketTexture);
        rocketCenterOffset = 20.f;
        (*rocketSprite).setOrigin(sf::Vector2f(static_cast<float>(rocketTexture.getSize().x)/2.f+rocketCenterOffset,static_cast<float>(rocketTexture.getSize().y/2.f)));
        status=StatusEngine::Normal;
        lastStatus=status;
        elapsedTime=0.f;
        overheatTime=0.f;
        Up=false;
        Down=false;
        Right=false;
        currentBoost=0.f;
        canBoost=true;
        direction=sf::Vector2f(0.f,0.f);
        angle=0.f;
        direction.x=std::cos(rad(angle));
        direction.y=std::sin(rad(angle));
        rocket.setPointCount(3);
        rocket.setFillColor(sf::Color::Yellow);
        rocket.setPoint(0,sf::Vector2f(0.f,0.f));
        rocket.setPoint(1,sf::Vector2f(0.f,40.f));
        rocket.setPoint(2,sf::Vector2f(70.f,20.f));
        rocket.setOrigin(sf::Vector2f(35.f,20.f));
        rocket.setRotation(sf::degrees(angle));
        rocket.setPosition(sf::Vector2f(startX/2.f,startY/2.f));
        (*rocketSprite).setScale({0.5,0.5});
        (*rocketSprite).setPosition(rocket.getPosition());
    }
    void Rocket::draw(sf::RenderWindow& win){
        win.draw(rocket);
        if(rocketSprite){win.draw(*rocketSprite);}
        
    }
    void Rocket::update(float dt, float worldHeight){
        
        if(Up){
            angle-=rotationSpeed*dt;
        }
        if (Down){
           angle+=rotationSpeed*dt;
        }
        
        direction.x=std::cos(rad(angle));
        direction.y=std::sin(rad(angle));

        if(status==StatusEngine::Normal){
            currentBoost=0.f;
            if(Right){
                status=StatusEngine::Boosting;
        }
        }
     
        else if(status==StatusEngine::Boosting){
            if(Right){
                if(currentBoost+boostBuildRate*dt<=boostMax){
                    currentBoost+=boostBuildRate*dt;
                }
           else{currentBoost=boostMax;
                status=StatusEngine::MaxSpeed;
                overheatTime=0.f;}
            
        }
        else{
            status=StatusEngine::Cooling;
        }
       

        }
        else if(status==StatusEngine::MaxSpeed){
             if(Right){
                bool stillSafe=updateOverheatTimer(dt);
                if(!stillSafe){
                    status=StatusEngine::Cooldown;
                }
            
        }
        else{status=StatusEngine::Cooling;}
        }

        else if(status==StatusEngine::Cooling){
            if(Right && canBoost){status=StatusEngine::Boosting;}

            else if(currentBoost>0.f){
                currentBoost-=boostDecay*dt;
                if(currentBoost<0.f){currentBoost=0.f;}}

            else{currentBoost=0.f;
                status=StatusEngine::Normal;
                canBoost=true;}
        }
        else if(status==StatusEngine::Cooldown){
            canBoost=hasCooldownExpired(dt);
            if(!canBoost){
            if(currentBoost>0.f){
                currentBoost-=overheatSpeedDrop*dt;
            if(currentBoost<0.f){currentBoost=0.f;}}

            }
            else{
                if(Right && canBoost){status=StatusEngine::Boosting;}
                else{status=StatusEngine::Normal;}
            }

            


        }

        if (status != lastStatus) {

    if (status == StatusEngine::Boosting || status == StatusEngine::MaxSpeed)
        rocketSprite->setTexture(rocketFlamesTexture);
    else
        rocketSprite->setTexture(rocketTexture);

    lastStatus = status;
}

        totalSpeed=baseSpeed+currentBoost;
      
        
        
     
        
        rocket.setRotation(sf::degrees(angle));
        rocket.move({(direction.x*totalSpeed)*dt, (direction.y*totalSpeed)*dt});

        sf::Vector2f pos=rocket.getPosition();
        float halfHeight=rocket.getGlobalBounds().size.y/2.f;
        pos.y=std::clamp(pos.y,halfHeight,worldHeight-halfHeight);
        rocket.setPosition(pos);
        (*rocketSprite).setPosition(rocket.getPosition());
        (*rocketSprite).setRotation(rocket.getRotation());
        

            
    }
    float Rocket::rad(float angle){
        return angle * 3.1415926f / 180.f;
    }
    sf::Vector2f Rocket::getPosition(){
        return sf::Vector2f{rocket.getPosition().x,rocket.getPosition().y};
    }
    std::string Rocket::getEngineCondition(){
        switch(status){
            case StatusEngine::Normal: return "Ready";
            case StatusEngine::Boosting: return "Running";
            case StatusEngine::MaxSpeed: return "Overheating";
            case StatusEngine::Cooling: return "Cooling";
            case StatusEngine::Cooldown: return "Overheated";
        }
        return "Unknown";
    }
    float Rocket::getSpeed(){
    return baseSpeed+currentBoost;
    }
    bool Rocket::hasCooldownExpired(float& dt){
        if(elapsedTime<timerCoolDown){
            elapsedTime+=dt;
            return false;
        }
        else{elapsedTime=0.f;
        return true;}
        return false;
    }
    bool Rocket::updateOverheatTimer(float& dt){
        if(overheatTime<boostDuration){
            overheatTime+=dt;
            return true;
        }
        else{overheatTime=0.f;
        return false;}
    }
    sf::Vector2f Rocket::getRocketPoint(int num){
        if(num>=rocket.getPointCount()){return rocket.getPosition();}
        return rocket.getTransform().transformPoint(rocket.getPoint(num));
    }
    float Rocket::getHp()const{return hp;}
    void Rocket:: takeDamage(float damage){
        hp-=damage;
        if(hp<0.f){
            hp=0.f;
        }
    }
    float Rocket::getCollisionDamage()const{
        return collisionDamage;
    }
    bool Rocket:: isDead()const{
        return hp<=0.f;
    }
    float Rocket::getHpMax()const{
        return hpMax;
    }

    void Rocket::reloadConfig(){
        baseSpeed=config.baseSpeed;
        boostBuildRate=config.boostBuildRate;
        boostMax=config.boostMax;
        baseSpeedDecay=config.baseSpeedDecay;
        boostDecay=config.boostDecay;
        hp=config.hpMax;
        hpMax=config.hpMax;
        boostDuration=config.boostDuration;
        overheatSpeedDrop=config.overheatSpeedDrop;
        timerCoolDown=config.timerCoolDown;
        rotationSpeed=config.rotationSpeed;
    }
   

 