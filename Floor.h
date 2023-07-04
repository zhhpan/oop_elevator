#ifndef FLOOR_H
#define FLOOR_H

#include "Rider.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::ostream;
using std::string;

class Floor
{
    const string NAME; // name of floor, for example: Mezzanine
    vector<Rider> upRiders; // affected by addNewRider, removeUpRiders,...
    vector<Rider> downRiders; // ...and removeDownRiders functions
    bool can_move[10][40] = {
            {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
            {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
            {true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false, false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
            {true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false, false,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true},
            {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
            {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
            {true,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true},
            {true,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true},
            {true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false},
            {true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false}
    };

public:
    Floor(const int, const char* const = "unnamed"); // name and location (inches above ground) of floor
    const int location; // inches above ground level
    inline int getLocation() const {return location;}
    inline bool hasRidersWaiting() const {return (!upRiders.empty() || !downRiders.empty());}
    inline bool hasUpRiders() const{return !upRiders.empty();}
    inline bool hasDownRiders() const{return !downRiders.empty();}
    bool isPreferredDirectionUp() const; // based on Rider with smallest ID
    void addNewRider( Rider&); // add to up- or down-vector
    vector<Rider> removeUpRiders(int,int,vector<Rider>&); // int is max #of riders...
    vector<Rider> removeDownRiders(int,int,vector<Rider>&); //...to move onto elevator
    bool get_available (int elevator_num, int floor_num) const;
};
#endif
