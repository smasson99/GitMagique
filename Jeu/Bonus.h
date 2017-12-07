#pragma once
#include "Spaceship.h"
#include <SFML\Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

namespace spaceShooter
{
    class Bonus
    {
    public:
        //Enum
        static enum BonusType
        {
            ScoreBonus_Type,
            BonusType_MAX
        };
        //Constructeur
        Bonus(const float radius, const Color color, const float bonusMagnitude, const float bonusDuration, const Vector2f pos);
        //Destructeur
        ~Bonus();
        //Update
        virtual void Update();
        //Dessiner
        void Draw(RenderWindow &mainWin);
        //Autres
        bool IsEnable();
        void Disable();
        void Enable();
        void Start(Vector2f pos);
        Vector2f GetPos();
        static void SubscribeToCollisions(Spaceship* subscriber);
        static void CleanUp();
    protected:
        float duration;
        float radius;
        float magnitude;
        Sprite* sprite;
        //temp
        static vector<Spaceship*> observers;
    private:
        //Variables logiques:
        //Horologe
        Clock clock;
        //Timer
        Time timer;
        //Status
        bool isEnable;
    };
}