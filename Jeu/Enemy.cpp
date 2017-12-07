//<sberube>
#include "Enemy.h"
using namespace spaceShooter;

vector<GameScene*> Enemy::scenes;

Enemy::Enemy() : Spaceship::Spaceship()
{
	isSlave = false;
	type = EnemyType::BASIC;
}

bool Enemy::Update(Vector2f target)
{
	if (sprite->getPosition().y < idlePosition)
	{
		Move(0, 1);
	}
	return curHealth >= 0;
}

void Enemy::SetColor(Color color)
{
	sprite->setColor(color);
}

//<smasson>

Enemy::~Enemy()
{
    delete enemyWeapon;
}

void Enemy::CleanUp()
{
    //Clean-up
    for (GameScene* curScene : scenes)
    {
        curScene = nullptr;
    }
    scenes.clear();
}
Projectile::ProjectileType spaceShooter::Enemy::GetProjectileType()
{
    return enemyWeapon->GetProjType();
}

void spaceShooter::Enemy::SubscribeToShoots(GameScene* scene)
{
    scenes.push_back(scene);
}
Vector2f spaceShooter::Enemy::GetDir()
{
    return Vector2f(0, 1);
}
Enemy::EnemyType Enemy::GetType() const
{
    return type;
}
//</smasson>

//</sberube>