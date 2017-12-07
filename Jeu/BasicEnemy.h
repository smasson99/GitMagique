#pragma once
#include "Enemy.h"
//<sberube>
namespace spaceShooter
{
	class BasicEnemy : public Enemy
	{
	public:
		BasicEnemy();
        ~BasicEnemy();
		bool Update(Vector2f target);
        static bool Init(char path[]);
        void AdjustVisual();
	private:
		bool goingRight;
        static Texture texture;
	};
}
//</sberube>