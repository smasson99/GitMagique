#pragma once
#include "Enemy.h"
//<sberube>
namespace spaceShooter
{
	static class Spawner
	{
	public:
		static void SetPosition(float x, float y);
		static Enemy SpawnMob(Enemies type);
	private:
	};
}
//</sberube>