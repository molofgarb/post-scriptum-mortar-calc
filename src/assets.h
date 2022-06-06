#ifndef ASSETS_H
#define ASSETS_H

#include <iostream>
#include <string>

class Asset {
public:
    Asset(const std::string& name);
    bool getStatus() const;
    virtual int report() const = 0;
private:
    friend std::ostream& operator<<(std::ostream& os, const Asset& rhs);

    std::string name;
    std::string imageName; //picture of asset
    bool status;
};

class TicketAsset: virtual public Asset {
public:
    TicketAsset(const std::string& name, int cost);
    int report() const;
private:
    friend std::ostream& operator<<(std::ostream& os, const TicketAsset& rhs);

    int total_cost;
    int death_cost; //ticket cost
};

class TimeAsset: virtual public Asset {
public:
    TimeAsset(const std::string& name, int resp_time);
    int report() const;
private:
    friend std::ostream& operator<<(std::ostream& os, const TimeAsset& rhs);

    int curr_time;
    int resp_time; //respawn time
};

class TickTimeAsset: public TicketAsset, public TimeAsset {
public:
    TickTimeAsset(const std::string& name, int cost, int time);
    int report() const;
private:
    friend std::ostream& operator<<(std::ostream& os, const TickTimeAsset& rhs);
};

#endif