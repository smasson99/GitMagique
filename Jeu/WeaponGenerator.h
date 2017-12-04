#pragma once
#include "Weapon.h"
//#include "Projectile.h"

namespace spaceShooter
{
    class WeaponGenerator
    {
    public:
        static Weapon* GetWeapon(Weapon::WeaponType type);
    private:
    };
}