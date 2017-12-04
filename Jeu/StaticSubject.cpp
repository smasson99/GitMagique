#include "StaticSubject.h"

using namespace spaceShooter;

vector<vector<Observer*>> StaticSubject::observers;
int StaticSubject::nbInstaces = 0;

spaceShooter::StaticSubject::StaticSubject()
{
    ++nbInstaces;
    no = nbInstaces;
    observers.push_back(vector<Observer*>());
}

spaceShooter::StaticSubject::~StaticSubject()
{
    //Clean-up
    for (Observer* curObserver : observers.at(no - 1))
    {
        delete curObserver;
    }
    observers.at(no - 1).clear();
    --nbInstaces;
}

void spaceShooter::StaticSubject::Sub(Observer * subscriber)
{
    observers.at(no - 1).push_back(subscriber);
}

vector<Observer*> spaceShooter::StaticSubject::GetCurObservers() const
{
    return observers.at(no-1);
}

bool spaceShooter::StaticSubject::HasObservers() const
{
    return observers.at(no).empty();
}
