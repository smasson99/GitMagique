#include "Weapon.h"

Weapon::Weapon(const float cadency, const int nbProjs, const Projectile::ProjectileType type, const Weapon::WeaponType wType) :nbProjs(nbProjs), cadency(cadency), projType(type), timerDur(seconds(cadency)), myType(wType)
{
    clock.restart();
}

Weapon::~Weapon()
{

}

bool Weapon::CanShoot()
{
    return clock.getElapsedTime().asSeconds() >= timerDur.asSeconds();
}

void Weapon::Shoot()
{
    clock.restart();
    --nbProjs;
}

Projectile::ProjectileType spaceShooter::Weapon::GetProjType() const
{
    return projType;
}

Weapon::WeaponType spaceShooter::Weapon::GetType() const
{
    return myType;
}

int spaceShooter::Weapon::GetNbProjs()
{
    return nbProjs;
}


