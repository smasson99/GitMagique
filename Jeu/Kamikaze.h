#pragma once
#include "Enemy.h"
#include "Bombe.h"
namespace spaceShooter
{
	class Kamikaze : public Enemy, public Bombe
	{
	public:
		Kamikaze();
		bool Update(Vector2f target);
		void Draw(RenderWindow &win);
	private:
		const float startSpeed = 0.01f;
		float curSpeed = startSpeed;
		float maxSpeed = 6;
	};
}