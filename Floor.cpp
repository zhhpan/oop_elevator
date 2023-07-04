#include "Floor.h"
#include "Rider.h"
#include <cstdlib>
using std::abs;

Floor::Floor(const int a, const char* const s ):NAME(s),location(a){};

bool Floor::get_available (int elevator_num, int floor_num) const{return can_move[elevator_num][floor_num];}
void Floor::addNewRider( Rider& rider)
{
    if(rider.getDestination().getLocation()>location)// if added rider's destination is greater than the floor's location
        upRiders.push_back(rider);// add rider to the upRiders vector
    else
        downRiders.push_back(rider);// add rider to the downRiders vector
}

vector<Rider> Floor::removeUpRiders(int max,int num,vector<Rider> &riders) // max = #of unused spaces on elevator
{
    vector<Rider> mveRiders;// create an empty vector for riders to be removed
    if(!upRiders.empty())// if there are any up riders
    {
        vector<Rider> remRiders;// create an empty vector for riders to remain on the floor
        for(int i=0;i<upRiders.size();i++)// traverse the upRiders vector
        {
            if(mveRiders.size()<max) {// if there are still spaces left on the elevator
                if (get_available(num,upRiders[i].f->getLocation()/20)) {
                    mveRiders.push_back(upRiders[i]);// add an upRider to the vector of riders to be removed
                    riders[upRiders[i].RiderID-1].isinelevator = true;
                } else
                    remRiders.push_back(upRiders[i]); // add an upRider to the vector of riders to remain on the floor
            }
            else
                remRiders.push_back(upRiders[i]); // add an upRider to the vector of riders to remain on the floor
        }
        upRiders=remRiders;// replace the upRiders vector with the vector of remaining riders
    }
    return mveRiders;
}

vector<Rider> Floor::removeDownRiders(int max,int num,vector<Rider> &riders)
{
    vector<Rider> mveRiders;// create an empty vector for riders to be removed
    if(!downRiders.empty())// if there are any up riders
    {
        vector<Rider> remRiders;// create an empty vector for riders to remain on the floor
        for(int i=0;i<downRiders.size();i++)// traverse the upRiders vector
        {
            if(mveRiders.size()<max) {// if there are still spaces left on the elevator
                if(get_available(num,downRiders[i].f->getLocation()/20)) {
                    mveRiders.push_back(downRiders[i]);// add an upRider to the vector of riders to be removed
                    riders[downRiders[i].RiderID-1].isinelevator = true;
                }else
                    remRiders.push_back(downRiders[i]); // add an upRider to the vector of riders to remain on the floor
            }
            else
                remRiders.push_back(downRiders[i]); // add an upRider to the vector of riders to remain on the floor
        }
        downRiders=remRiders;// replace the upRiders vector with the vector of remaining riders
    }
    return mveRiders;
}

bool Floor::isPreferredDirectionUp() const
{
    if(downRiders.size()==0)// if there are no downRiders, return true
        return true;
    if(upRiders.size()==0)// if there are no upRiders
        return false;
    if(upRiders[0]<downRiders[0])// if the ID of the first upRider is less than that of the first downRider
        return true;
    return false;
}
