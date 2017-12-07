#include "ProjectileGenerator.h"
#include "Bombe.h"
Projectile * spaceShooter::ProjectileGenerator::GetProjectile(Projectile::ProjectileType type)
{
    Projectile* res = nullptr;

    switch (type)
    {
    case Projectile::ProjectileType::BASIC:
        res = new Projectile(4.5f, 15, Player::GetInstance()->GetSprite()->getColor(), 6.5f, Player::GetInstance());
        break;
	case Projectile::ProjectileType::BOMB:
		res = new Bombe(15, 15, Player::GetInstance()->GetSprite()->getColor(), 4.5f, Player::GetInstance());
		break;
	case Projectile::ProjectileType::BOMB_PROJ:
		res = new BombProj(100, 4.5f, 15, Color::Red, 3.5f, Player::GetInstance());
		break;
    }

    return res;
}
