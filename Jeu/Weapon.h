#pragma once
#include <SFML\Graphics.hpp>
#include "Projectile.h"

using namespace sf;

namespace spaceShooter
{
    class Weapon
    {
    public:
        static enum WeaponType
        {
            BASIC_WEAPON
        };
        Weapon(const float cadency, const int nbProjs, const Projectile::ProjectileType type, const Weapon::WeaponType wType);
        ~Weapon();
        bool CanShoot();
        void Shoot();
        Projectile::ProjectileType GetProjType() const;
        Weapon::WeaponType GetType() const;
        int GetNbProjs();
    private:
        int nbProjs;
        float cadency;
        Clock clock;
        Time timerDur;
        Projectile::ProjectileType projType;
        Weapon::WeaponType myType;
    };
}