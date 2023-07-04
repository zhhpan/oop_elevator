#ifndef Building_h
#define Building_h
#include "Elevator.h"
#include "Floor.h"
#include <vector>
#include <iostream>
using std::ostream;
using std::vector;
class Building
{
    int time;
    vector<Elevator*> elevator;
    vector<Floor*> floor;
    vector<Rider>riders;

public:
    bool isRider[300];//judge if every rider has finished the ride
    Building();
    ~Building();
    Building& step(int,vector<int>&);
    Building& step(vector<int>&);
    void run(vector<Rider> &riders,vector<Floor*> &floor);
    inline int getFloorCount() const{return floor.size();} // return #of floors in the vector of Floor*'s
    inline int getElevatorCount() const{return elevator.size();}// return #of elevators in the vector of Elevator*'s
    friend ostream& operator<<(ostream&, const Building&);//overloading the operator <<
    void ElevatorRun(vector<int>&);
    void show();
};
#endif

