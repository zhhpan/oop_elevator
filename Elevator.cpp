#include "Elevator.h"
#include <cstdlib>
#include <iostream>
using std::abs;
class Floor;
int Elevator::elevatorID=0;
Elevator::Elevator(const int c, const int s, const Floor& f):ID(elevatorID),capacity(c),speed(s),toFloor(0)
{
    setIdle();
    location = f.getLocation();
    openDoor();
}
bool Elevator::isNearDestination()const
{
    if(hasADestination())
    {
        if(abs(toFloor->getLocation()-location)<=speed||abs(toFloor->getLocation()-abs(location))<=speed)
            return true;
        else
            return false;
    }
    else
        return false;
}
void Elevator::moveToDestinationFloor()
{
    location=toFloor->getLocation();
}
ostream& operator<<(ostream& out, const Elevator& El)
{
    out<< El.rider.size() << " riders in elevator. ";
    if(El.location>0)
        out<<"Elevator is: "<<abs(El.location)/20+1<<"th floor, ";
    else if(El.location<0)
        out<<"Elevator is: "<<abs(El.location)/20+1<<"th floor, ";
    else
        out<<"1st floor, ";
    if(El.isDirectionDown())
        out<<"Going Down, ";
    else if(El.isDirectionUp())
        out<<"Going Up, ";
    else
        out<<"Idle, ";
    std::cout<<std::endl;
    if(!El.rider.empty()) {
        for (Rider i: El.rider) {
            std::cout << i.RiderID << "-" << i.getDestination().location/20+1<<" ";
        }
        std::cout << std::endl;
    }
    return out;
}
vector<Rider> Elevator::removeRidersForDestinationFloor(vector<Rider> &riders)
{
    // create empty vector of removed riders to be used as return value
    vector<Rider> removedRiders;
    // if elevator has any riders
    if(rider.size()!=0)
    {
        vector<Rider> remainingRiders;// create an empty vector for riders who remain on elevator
        for(int i=0;i<rider.size();i++)// traverse vector of current riders
        {
            if(rider[i].getDestination().getLocation() == toFloor->getLocation()){// if a rider's destination floor is same as elevator's destination...
                removedRiders.push_back(rider[i]);// add rider to vector of removed riders
                riders[rider[i].RiderID-1].setisinDestination();
                riders[rider[i].RiderID-1].isinelevator = false;
            }
            else
                remainingRiders.push_back(rider[i]);  // add rider to vector of remaining riders
        }
        rider=remainingRiders;  // reassign elevator rider vector to vector of remaining riders
    }
    return removedRiders;  // return vector of removed riders
}

void Elevator::addRiders(const vector<Rider>& riders,int num)
{
    for(int i=0;i<riders.size();i++)// traverse the parameter vector
    {
        if(rider.size()< capacity)  // if there is still room on the elevator
            rider.push_back(riders[i]);  // add the rider to the elevator's rider vector
    }
}

void Elevator::setDestinationBasedOnRiders()
{
    if(rider.size()==0)// if there are no riders on the elevator
        return;
    toFloor = &rider[0].getDestination();// set elevator's destination to the zeroth Rider's destination
    for(int i=0;i<rider.size();i++)// traverse the vector of elevator riders
    {
        int ridDest = abs(rider[i].getDestination().getLocation()-location);// get the absolute value of the distance from the elevator to the rider's destination floor
        int elDest = abs(toFloor->getLocation()-location);// get the absolute value of the distance from the elevator to the elevator's destination floor
        if(ridDest<elDest)// if closer to the rider's destination than to the elevator's destination
            toFloor = &rider[i].getDestination();// set elevator's destination to the rider's destination
    }
}