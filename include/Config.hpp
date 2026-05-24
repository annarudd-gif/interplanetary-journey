#pragma once

class Config
{
public:
    float baseSpeed = 300.f;
    float timerCoolDown = 20.f;
    float boostDuration = 5.f;
    float overheatSpeedDrop = 40.f;
    float baseSpeedDecay = 20.f;
    float boostBuildRate = 120.f;
    float boostMax = 400.f;
    float boostDecay = 80.f;
    float hpMax = 500.f;
    float rotationSpeed = 50.f;

    
    float spawnDelay=0.5f;
    float minAstRadius=30.f;
    float maxAstRadius=60.f;



    bool load();
    bool save();

};