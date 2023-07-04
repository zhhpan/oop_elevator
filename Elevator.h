#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <iostream>
#include "Floor.h"
#include "Rider.h"
#include <vector>

using std::vector;
using std::ostream;

class Elevator
{
    static const int IDLE=0; // a unique numeric code
    static const int UP=1; // another unique numeric code
    static const int DOWN=2; // yet another unique numeric code
    const int ID; // a unique identifier
    const int capacity; // max number of riders, set in constructor
    const int speed; // inches per second, up or down, set in constructor
    Floor* toFloor; // destination floor, initialized in constructor to zero
    int location; // inches above ground level, initialized in constructor based on starting floor
    int direction; // equal to IDLE, UP, DOWN, initialized to IDLE in constructor
    bool doorOpen; // initialized to true in constructor
    const bool can_move[10][40] = {
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
    vector<Rider> rider;
    static int elevatorID; // initialize to zero; use to assign unique ID to each elevator

public:
    int run_time = 0;
    Elevator(const int, const int, const Floor&); // capacity, speed, and starting floor
    inline int getRiderCount() const{return rider.size();} // return size of riders vector
    inline int getAvailableSpace() const{return (capacity-rider.size());} // return capacity minus size of riders vector
    inline bool isDoorOpen() const {return doorOpen;} // returns value of doorOpen
    inline bool isIdle() const {return direction == IDLE;} // returns true if direction is IDLE
    inline bool isDirectionUp() const {return direction == UP;} // returns true if direction is UP
    inline bool isDirectionDown() const {return direction == DOWN;} // returns true if direction is DOWN
    inline void closeDoor(){doorOpen=false;} // set doorOpen to false
    inline void openDoor(){doorOpen=true;} // set doorOpen to true
    inline void setIdle(){direction=IDLE;} // set direction to IDLE
    inline void setDirectionUp(){direction=UP;} // set direction to UP
    inline void setDirectionDown(){direction=DOWN;} // set direction to DOWN
    inline void moveUp(){location+=speed;} // increment location by #inches per second speed of the elevator
    inline void moveDown(){location-=speed;} // decrement location by #inches per second speed of the elevator
    inline void setDestination( Floor* floor){toFloor=floor;} // set toFloor pointer
    inline Floor& getDestination() const {return *toFloor;} // return reference to toFloor
    inline int getLocation() const{return location;} // return location value
    inline bool hasADestination() const{return toFloor != 0;} // return false if toFloor is zero
    void addRiders(const vector<Rider>&, int num); // copy riders from parameter vector to riders vector
    void setDestinationBasedOnRiders(); // reset toFloor based on riders' destinations
    bool isNearDestination() const; // true if distance to destination is less than OR EQUAL TO the speed
    void moveToDestinationFloor(); // set location to that of destination floor (if there is one)
    friend ostream& operator<<(ostream&, const Elevator&);
    vector<Rider> removeRidersForDestinationFloor(vector<Rider> &riders);
    inline bool get_available (int elevator_num, int floor_num){return can_move[elevator_num][floor_num];}
};
#endif