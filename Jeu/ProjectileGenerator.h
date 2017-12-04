#pragma once
#include "Player.h"
#include "Projectile.h"

namespace spaceShooter
{
    class ProjectileGenerator
    {
    public:
        static Projectile* GetProjectile(Projectile::ProjectileType type);
        
    private:
    };
}
