#include "Config.hpp"
#include "json.hpp"
#include "fstream"
#include "iostream"

using json = nlohmann::json;

bool Config::load(){

    std::ifstream file("assets/config.json");

    if(!file.is_open()){
        return false;
    }

    json config;
    file >> config;
    baseSpeed=config["rocket"]["baseSpeed"];
    timerCoolDown=config["rocket"]["timerCoolDown"];
    boostDuration=config["rocket"]["boostDuration"];
    overheatSpeedDrop=config["rocket"]["overheatSpeedDrop"];
    baseSpeedDecay=config["rocket"]["baseSpeedDecay"];
    boostBuildRate=config["rocket"]["boostBuildRate"];
    boostMax=config["rocket"]["boostMax"];
    boostDecay=config["rocket"]["boostDecay"];
    hpMax=config["rocket"]["hpMax"];
    rotationSpeed=config["rocket"]["rotationSpeed"];

    spawnDelay=config["game"]["spawnDelay"];
    minAstRadius=config["game"]["minAstRadius"];
    maxAstRadius=config["game"]["maxAstRadius"];


    return true;
}

bool Config::save()
{
    json j;

    j["rocket"]["baseSpeed"] = baseSpeed;
    j["rocket"]["timerCoolDown"] = timerCoolDown;
    j["rocket"]["boostDuration"] = boostDuration;
    j["rocket"]["overheatSpeedDrop"] = overheatSpeedDrop;
    j["rocket"]["baseSpeedDecay"] = baseSpeedDecay;
    j["rocket"]["boostBuildRate"] = boostBuildRate;
    j["rocket"]["boostMax"] = boostMax;
    j["rocket"]["boostDecay"] = boostDecay;
    j["rocket"]["hpMax"] = hpMax;
    j["rocket"]["rotationSpeed"] = rotationSpeed;

    j["game"]["spawnDelay"] = spawnDelay;
    j["game"]["minAstRadius"] = minAstRadius;
    j["game"]["maxAstRadius"] = maxAstRadius;

    std::ofstream file("config.json");

    file << j.dump(4);

    return true;
}