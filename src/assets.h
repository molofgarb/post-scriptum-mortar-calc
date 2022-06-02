#ifndef ASSETS_H
#define ASSETS_H

#include <iostream>
#include <fstream>
#include <string>

class Asset {
public:
    Asset(const std::string& name);
    virtual bool status() const = 0;
private:
    std::string name;
    bool status;
};

class TicketAsset: public Asset {
public:
private:
    int cost; //ticket cost
    int amount; //amount of this asset
};

class TimeAsset: public Asset {
public:
private:
    int time; //respawn time
};

#endif