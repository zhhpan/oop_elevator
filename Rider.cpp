#include "Floor.h"
#include "Rider.h"
int Rider::copyID = 1;
Rider::Rider(std::queue<int> q,Floor &m):  f(&m), RiderID(copyID)
{
    floor_queue=q;
    copyID++;
}
bool Rider:: operator==(const Rider& b) const
{
    bool result = false;
    if (RiderID== b.RiderID)result= true;

    return result;
}
bool Rider:: operator<(const Rider& b) const
{
    bool result = false;
    if (RiderID< b.RiderID)result= true;

    return result;
}
Rider& Rider::operator=(const Rider& a)
{
    const_cast<int&>(RiderID) = a.RiderID;
    const_cast<const Floor*&>(f)=a.f;
    return *this;
}
