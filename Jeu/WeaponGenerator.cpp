#include "WeaponGenerator.h"

Weapon * spaceShooter::WeaponGenerator::GetWeapon(Weapon::WeaponType type)
{
    Weapon* res = nullptr;

    switch (type)
    {
    case Weapon::WeaponType::BASIC_WEAPON:
        res = new Weapon(0.22f, 0, Projectile::ProjectileType::BASIC, Weapon::WeaponType::BASIC_WEAPON);
        break;
    }

    return res;
}
