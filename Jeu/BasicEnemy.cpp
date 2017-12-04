//<sberube>
#include "BasicEnemy.h"
#include "Background.h"
#include <iostream>
#include "WeaponGenerator.h"
#include "GameScene.h"

using namespace spaceShooter;
static float leftLimit;
static float rightLimit;
Texture BasicEnemy::texture;

BasicEnemy::BasicEnemy() : Enemy::Enemy()
{
    //<smasson>
    //Déclaration des variables
    enemyWeapon = WeaponGenerator::GetWeapon(Weapon::BASIC_WEAPON);

    //Initialisations préparatoires...
    //</smasson>
    sprite->setScale(0.35f, 0.35f);
	speed = 3;
	SetColor(Color::Green);
	sprite->setRotation(180);

	if ((rand() % 2 + 1) == 2)
	{
		goingRight = true;
	}
	else
	{
		goingRight = false;
	}
}
spaceShooter::BasicEnemy::~BasicEnemy()
{
}
bool BasicEnemy::Update(Vector2f target)
{
	Enemy::Update(target);
	if (sprite->getPosition().y >= idlePosition)
	{
		if (goingRight)
		{
			Move(1, 0);
			if (sprite->getPosition().x >= Background::RightLimit() - 20)
			{
				goingRight = false;
			}
		}
		else
		{
			Move(-1, 0);
			if (sprite->getPosition().x <= Background::LeftLimit() + 20)
			{
				goingRight = true;
			}
		}
	}
	if (sprite->getPosition().x > target.x - 20 && sprite->getPosition().x < target.x + 20)
	{
		// Shoot
        //<smasson>
        //Si l'ennemi peut tirer:
        if (enemyWeapon->CanShoot())
        {
            //Avertir les scènes que nous avons tiré et tirer, évidemment
            enemyWeapon->Shoot();
            for (GameScene* curScene : scenes)
            {
                curScene->NotifyAShoot(this);
            }
        }
        //</smasson>
	}
	return true;
}
//</sberube>

//<smasson>
bool BasicEnemy::Init(char path[])
{
    if (!texture.loadFromFile(path))
        return true;
    return true;
}
void BasicEnemy::AdjustVisual()
{
    sprite->setTexture(texture);
    sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
//</smasson