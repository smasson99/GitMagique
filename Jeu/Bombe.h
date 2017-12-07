#pragma once
#include "Projectile.h"
#include <vector>

namespace spaceShooter
{
	//////////////////////////////////////////////
	// Class Bombe
	//////////////////////////////////////////////
	class GameScene;
	class Bombe : public Projectile
	{
	public:

		Bombe(const float x, const float y, const Color color, const float speed, Spaceship* owner);
		//void Update();
		//float GetRadius();
		Vector2f Bombe::GetPosition();
		void Explode();
		static void SubExplosion(GameScene *scene);
	private:

	};

	//////////////////////////////////////////////
	// Class BombProj
	//////////////////////////////////////////////

	class BombProj : public Projectile
	{
	public:
		BombProj(const float radius, const float x, const float y, const Color color, const float speed, Spaceship* owner);
		void Update();
	private:
		float radius;
	};
}