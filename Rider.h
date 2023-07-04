#ifndef Rider_H
#define Rider_H
#include "queue"
class Floor;
class Rider
{
    static int copyID;

public:
    int wait_time = 0;
    bool isinelevator = false;
    bool isinDestination= true;//check if the rider is in destination
    inline void setisinDestination(){isinDestination=true;}
    std::queue<int> floor_queue;//queue of the rider needing to go to
    Floor*  f;//the next floor of destination
    const int RiderID;//every rider has an ID which is different with others
    Rider& operator=(const Rider&);
    Rider(std::queue<int> q,Floor& m);
    inline Floor& getDestination() {return *f;}
    bool operator==(const Rider&) const;
    bool operator<(const Rider&) const;
    int waitime=0;//when a rider is in his destination, he will wait for 2 seconds,but the beginning wait time is 2s
};
#endif
