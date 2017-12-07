#pragma once
#include "Projectile.h"
#include <vector>

namespace spaceShooter
{
	class Bombe : public Projectile
	{
	public:
		struct BombProj : public Projectile
		{
		public:
			BombProj(const float x, const float y, const Color color, const float speed, Spaceship* owner) : Projectile::Projectile(x, y, color, speed, owner)
			{
				// On met le bon sprite
				
			}
			void Update(float x, float y)
			{
				Projectile::Update();
				if (false) // Si le  projectile est trop éloigné du centre d'explosion (x, y en param comparé a explosionRadius)...
				{
					isEnable = false; // Il disparait
				}
			}
		private:
			
		};
		Bombe(const float x, const float y, const Color color, const float speed, Spaceship* owner);
		void Update();
		void Draw(RenderWindow &win);
		float GetRadius();
		void Explode();
	private:
		float explosionRadius;
		bool exploding;
		vector<BombProj> explosion;
	};
}