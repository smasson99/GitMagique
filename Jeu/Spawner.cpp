#include "Spawner.h"
#include "BasicEnemy.h"
using namespace spaceShooter;
static float posX;
static float posY;
Enemy Spawner::SpawnMob(Enemies type)
{
	if (type == Enemies::BASIC)
	{
		BasicEnemy retVal;
		retVal.SetPosition(posX,posY);
	}
	else if (type == Enemies::KAMIKAZE)
	{

	}
	else if (type == Enemies::REFLECTOR)
	{

	}
	else if (type == Enemies::QUEEN)
	{

	}
	else if (type == Enemies::BOSS_CANNON)
	{

	}
	Enemy das;
	return das;
}

void Spawner::SetPosition(float x, float y)
{
	posX = x;
	posY = y;
}