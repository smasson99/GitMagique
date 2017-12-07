#include "Bombe.h"
#include "GameScene.h"
using namespace spaceShooter;

//////////////////////////////////////////////
// Class Bombe
//////////////////////////////////////////////

static vector<GameScene*> explObservers;

Bombe::Bombe(const float x, const float y, const Color color, const float speed, Spaceship* owner) : Projectile(x, y, color, speed, owner)
{
	// On ajoute un sprite propre à la bombe

}
//void Bombe::Update()
//{
//	Projectile::Update();
//}
//float Bombe::GetRadius()
//{
//	return explosionRadius;
//}

void Bombe::Explode()
{
	for (size_t i = 0; i < explObservers.size(); i++)
	{
		explObservers.at(i)->NotifyAnExplosion(this);
		isEnable = false;
	}
}
Vector2f Bombe::GetPosition() { return shape->getPosition(); }
void Bombe::SubExplosion(GameScene *scene)
{
	explObservers.push_back(scene);
}
//////////////////////////////////////////////
// Class BombProj
//////////////////////////////////////////////

BombProj::BombProj(const float radius, const float x, const float y, const Color color, const float speed, Spaceship* owner) : Projectile(x, y, color, speed, owner)
{
	// On met le bon sprite
	this->radius = radius;
}
void BombProj::Update()
{
	Projectile::Update();
	static float originalX = GetPosition().x;
	static float originalY = GetPosition().y;
	// Si le  projectile est trop éloigné du centre d'explosion
	if (GetPosition().x > originalX + radius || GetPosition().x < originalX - radius ||
		GetPosition().y > originalY + radius || GetPosition().y < originalY - radius)
	{
		isEnable = false;
	}
}