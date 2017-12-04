#pragma once
//<sberube>
#include "Spaceship.h"
#include "Weapon.h";
//temp
#include <iostream>
//
using namespace std;

namespace spaceShooter
{
    //foward declaration
    class GameScene;

	enum Enemies
	{
		BASIC,
		KAMIKAZE,
		QUEEN,
		REFLECTOR,
		BOSS_CANNON
	};
	class Enemy : public Spaceship
	{
	public:
		Enemy();
		virtual bool Update(Vector2f target);
		void SetColor(Color color);
        //<smasson>
        ~Enemy();
        static void CleanUp();
        Projectile::ProjectileType GetProjectileType();
        static void SubscribeToShoots(GameScene* scene);
        Vector2f GetDir();
        //</smasson>
	protected:
		Time lastFire;
		Time cadency;
		Clock fireClock;
		bool isSlave;
		Enemies type;
		Color color;
		int idlePosition = (rand() % 10 + 1) * 10 + 30;
        //temp
        static vector<GameScene*> scenes;
        //
        //<smasson>
        Weapon* enemyWeapon;
        //</smasson>
	};
}
//</sberube>