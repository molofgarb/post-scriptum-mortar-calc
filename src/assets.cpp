#include "assets.h"

#include <iostream>
#include <string>

// ============ Asset ============
Asset::Asset(const std::string& name): name(name), imageName(""),
    status(true) {}

bool Asset::getStatus() const {
    return status; }

// ============ TicketAsset ============
TicketAsset::TicketAsset(const std::string& name, int cost):
    Asset(name), total_cost(0), death_cost(cost) {}

//reports how many tickets have been lost
int TicketAsset::report() const {

}

// ============ TimeAsset ============
TimeAsset::TimeAsset(const std::string& name, int resp_time):
    Asset(name), curr_time(0), resp_time(resp_time) {}

//reports how much time until respawn
int TimeAsset::report() const {

}

// ============ TickTimeAsset ============
TickTimeAsset::TickTimeAsset(const std::string& name, int cost, int time):
    Asset(name), TicketAsset(name, cost), TimeAsset(name, time) {}

