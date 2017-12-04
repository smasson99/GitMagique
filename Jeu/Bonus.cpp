#include "Bonus.h"
#include "Spaceship.h"
#include <iostream>

/*
Sources des icons des bonus:
https://thenounproject.com


*/

using namespace spaceShooter;

vector<Spaceship*> Bonus::observers;

spaceShooter::Bonus::Bonus(const float radius, const Color color, const float bonusMagnitude, const float bonusDuration, const Vector2f pos):radius(radius), magnitude(bonusMagnitude), duration(bonusDuration), timer(seconds(bonusDuration))
{
    //Création de la sprite
    sprite = new Sprite();
    sprite->setColor(color);
    sprite->setPosition(pos);
    sprite->setScale(Vector2f(radius, radius));
    //Initialisation des variables par défaut
    isEnable = false;
}

spaceShooter::Bonus::~Bonus()
{
    //Clean-Up
    delete sprite;

    //Nettoyage des adresses
    sprite = nullptr;
}

void spaceShooter::Bonus::Update()
{
    //Bouger la shape vers le bas
    sprite->move(0, 1);

#pragma region:Collisions
    //Pour chaque observateur
    for (Spaceship* curObserver : observers)
    {
        //S'il y a une collision entre l'observateur et le bonus
        if (sprite->getGlobalBounds().intersects(curObserver->GetSprite()->getGlobalBounds()))
        {
            //Avertir l'observateur
            curObserver->NotifyBonusCollision(this);
            //Nous sommes disable
            Disable();
            //Debug
            std::cout << "Collision avec un bonus." << std::endl;
            //C'est cet observateur qui a le bonus
            break;
        }
    }
#pragma endregion

}

void spaceShooter::Bonus::Draw(RenderWindow & mainWin)
{
    mainWin.draw(*sprite);
}

bool spaceShooter::Bonus::IsEnable()
{
    return isEnable;
}

void spaceShooter::Bonus::Disable()
{
    isEnable = false;
}

void spaceShooter::Bonus::Enable()
{
    isEnable = true;
}

void spaceShooter::Bonus::Start(Vector2f pos)
{
    sprite->setPosition(pos);
    isEnable = true;
}

Vector2f spaceShooter::Bonus::GetPos()
{
    return sprite->getPosition();
}

void spaceShooter::Bonus::SubscribeToCollisions(Spaceship * subscriber)
{
    observers.push_back(subscriber);
}

void spaceShooter::Bonus::CleanUp()
{
    for (Spaceship* curObserver : observers)
    {
        curObserver = nullptr;
    }
    observers.clear();
}
