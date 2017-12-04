#include "Subject.h"
#include "Observer.h"

using namespace spaceShooter;

Subject::Subject()
{
}

Subject::~Subject()
{
    for (Observer* curObs : observers)
    {
        delete curObs;
    }
    observers.clear();
}

void spaceShooter::Subject::Sub(Observer * subscriber)
{
    observers.push_back(subscriber);
}

bool spaceShooter::Subject::HasObservers() const
{
    return observers.empty();
}
