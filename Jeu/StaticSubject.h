#pragma once
#include "Observer.h"
//Temporaire, nous prenons un vecteur en attendant la structure de données
#include <vector>
using namespace std;


namespace spaceShooter
{
    class StaticSubject
    {
    public:
        StaticSubject();
        ~StaticSubject();
        void Sub(Observer* subscriber);
        vector<Observer*> GetCurObservers() const;
        bool HasObservers() const;
    protected:
        static vector<vector<Observer*>> observers;
        static int nbInstaces;
    private:
        int no;
    };
}