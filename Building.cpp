#include "Building.h"
#include "Floor.h"
#include "Rider.h"
#include "Elevator.h"
#include <iostream>
using std::ostream;
using std::endl;
using std::cout;

#include <vector>
using std::vector;

void getDifferentInts(int ,  std::queue<int>& );

Building::Building()
{
    time=0;
    for (bool & i : isRider) {
        i=false;
}
    for(int i = 0; i <40;++i){
        floor.push_back(new Floor(20*i));//40 floor
    }
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));
    elevator.push_back(new Elevator(12,20,*floor[0]));//10 elevators
}
Building::~Building()
{
    for(int i=0; i<floor.size();i++)
        delete floor[i];
    for(int i=0; i<elevator.size();i++)
        delete elevator[i];
}

ostream& operator<<(ostream& out, const Building& b)
{
    out<<"\n\nTime= "<< b.time << endl;
    for(int i=0; i<(b.elevator).size();i++)
        out<<*(b.elevator[i])<<endl;
    return out;
}

Building& Building::step(int r,vector<int>& num)
{
    for(int i=r-20; i< r;i++)
    {
        // create a rider with randomly selected from- and to-floors
        std::queue<int> q;
        getDifferentInts(getFloorCount(),q);
        riders.push_back(Rider(q, *floor[q.front()]));
        isRider[i]= true;
        //floor[0]->addNewRider(riders.at(i));
    }
    Building::run(riders,floor);
    Building::ElevatorRun(num);
    time++;

    return *this;
}


Building &Building::step(vector<int>& num) {
    Building::run(riders,floor);
    Building::ElevatorRun(num);
    time++;
    return * this;
}

void Building::run(vector<Rider> &riders,vector<Floor*>&floor) {
    auto first = riders.begin();
    auto last = riders.end();
    while (first != last) {//ergodic every rider
        if (isRider[first->RiderID-1]) {// if he has not finished
            if( !first->isinelevator && !first->isinDestination){
                first -> wait_time++;
            }
            if (first->isinDestination) {//if he has got a destination
                if (first->floor_queue.empty()) {//if the floor_queue is empty
                    isRider[first->RiderID-1] = false;//he finishes the ride
                    continue;
                }
                else if (first->waitime != 0) {//if they still have wait time
                    first->waitime--;//wait time need to cut one second;

                } else {
                    int a = first->getDestination().location / 20;//get the location where he is in now
                    first->floor_queue.pop();//pop the floor_queue
                    first->isinDestination= false;//change the 'isinDestination' to false
                    first -> waitime = 2;
                    if (first->floor_queue.empty()) {//if the floor_queue is empty
                        isRider[first->RiderID-1] = false;//he finishes the ride
                        continue;
                    }
                    first->f = floor[first->floor_queue.front()];//floor.at(first -> floor_queue.front());
                    floor[a]->addNewRider(*first);//he is waiting for an elevator
                }
            }
        }
        ++first;
    }
}
void Building::ElevatorRun(vector<int>& num) {
    int n=0;
    for (int e = 0; e < getElevatorCount(); e++) {
        n+=elevator[e]->getRiderCount();
        if(!elevator[e]->isIdle()){
            ++elevator[e] -> run_time;
        }
        if (!(elevator[e]->isDoorOpen())) {// if elevator door is closed
            if (!(elevator[e]->isNearDestination())) {// if not near enough to destination to reach it in this time step, continue moving
                if (elevator[e]->isDirectionUp()) elevator[e]->moveUp();// if elevator direction is up, move up
                else elevator[e]->moveDown(); // move down
            }
            else {
                elevator[e]->moveToDestinationFloor();// tell elevator to move to its destination floor
                elevator[e]->openDoor();// tell elevator to open its door
                elevator[e]->removeRidersForDestinationFloor(riders);// tell elevator to remove riders for its destination floor
                Floor *f=&(elevator[e]->getDestination());// get a non-const pointer to the elevator's destination floor
                if (elevator[e]->getRiderCount() == 0) {// if elevator is empty, choose a direction based on longest-waiting rider
                    if((!f->hasUpRiders())&&(!f->hasDownRiders()))
                        elevator[e] ->setIdle();
                    else if (f->isPreferredDirectionUp()) // if the floor's chosen direction is up
                        elevator[e]->setDirectionUp(); // tell elevator to set its direction to up
                    else
                        elevator[e]->setDirectionDown();// tell elevator to set its direction to down
                }
                if (elevator[e]->getAvailableSpace() > 0 && elevator[e]->get_available(e,f->getLocation()/20)) {// if there is space in the elevator after letting off riders, board new ones
                    if (elevator[e]->isDirectionUp()){// if elevator direction is up, board up-riders
                        elevator[e]->addRiders(f->removeUpRiders(elevator[e]->getAvailableSpace(),e,riders),e);
                    }
                    else //board down-riders
                        elevator[e]->addRiders(f->removeDownRiders(elevator[e]->getAvailableSpace(),e,riders),e);
                }
                elevator[e]->setDestinationBasedOnRiders();// reassess elevator destination based on its riders
            }
        } else {
            if (elevator[e]->getRiderCount() > 0)// if elevator has any riders
                elevator[e]->closeDoor(); // tell elevator to close its door
            else
                elevator[e]->setIdle();// tell elevator to go idle
        }
    }
    num.push_back(n);
    for (int i = 0; i < getFloorCount(); i++) {
        if (!(floor[i]->hasRidersWaiting()))continue;// if there are no riders waiting on this floor, continue with next floor

        for (int j = 0; j < getElevatorCount(); j++) {// look at each elevator to see if it needs to be sent here
            if(!elevator[j] ->get_available(j,i))// check if the elevator could reach the floor
                continue;
            int loc = elevator[j]->getLocation() - floor[i]->getLocation();// get elevator's relative location
            if (elevator[j]->isIdle()) {// if this elevator is idle
                if (loc > 0)elevator[j]->setDirectionDown();// if elevator is above the floor, set elevator direction to down
                else elevator[j]->setDirectionUp();
                elevator[j]->setDestination(floor[i]);// set elevator's destination to this floor
                elevator[j]->closeDoor();// tell elevator to close its door
            } else if (floor[i]->hasUpRiders() && elevator[j]->isDirectionUp()) {
                int g = (elevator[j])->getDestination().getLocation() - (floor[i])->getLocation();// get distance from elevator's destination floor to this floor
                if (g < 0 && loc > 0)// if elevator is below floor and elevator destination is above this floor
                    elevator[j]->setDestination(floor[i]);// set elevator's destination to this floor
            }
            else if (floor[i]->hasDownRiders() && elevator[j]->isDirectionDown()) {// if there are riders on this floor waiting to go down, and the elevator is going down
                int g = (elevator[j]->getDestination()).getLocation() - (floor[i])->getLocation();// get distance from elevator's destination floor to this floor
                if (g > 0 && loc > 0)// if elevator is above floor and elevator destination is below this floor
                    elevator[j]->setDestination(floor[i]);// set elevator's destination to this floor
            }
        }

    }

}

void Building::show() {
    for (int i = 0; i < riders.size(); i++) {
        cout << "Rider "<<riders[i].RiderID <<"th---------wait time is " <<riders[i].wait_time<<std::endl;
    }
    for (int i = 0; i < elevator.size(); i++) {
        cout << "The elevator E"<< i<< "---------running time is "<<elevator[i]->run_time << std::endl;
    }
}

void getDifferentInts(int max, std::queue<int >&q)
{
    while(!q.empty()){//insure queue is empty
        q.pop();
    }
    int num=rand() % 8;//create a rand number as the number of circulating
    num+=2;
    int b=100;
    int a=1;
    q.push(0);
    for(int i=0;i<num;++i){
        do{
            b=rand() % max;//create a rand number different with the next one
            if(b!=a&&b!=0){
                a=b;
                break;
            }
        }
        while(true);
        q.push(b);//push the rand number
    }
    q.push(0);//finally push 0 to queue
}