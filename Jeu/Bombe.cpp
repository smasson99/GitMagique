#include "Bombe.h"
using namespace spaceShooter;

Bombe::Bombe(const float x, const float y, const Color color, const float speed, Spaceship* owner) : Projectile(x, y, color, speed, owner)
{
	// On ajoute un sprite propre à la bombe

}
void Bombe::Update()
{
	// Avec explosion
	if (exploding)
	{
		
		for (size_t i = 0; i < explosion.size(); i++)
		{
			explosion.at(i).Update(shape->getPosition().x, shape->getPosition().y);
		}
	}
	// Sans explosion
	else
	{
		Projectile::Update();
	}
}
float Bombe::GetRadius()
{
	return explosionRadius;
}

void Bombe::Explode()
{
	// On charge l'explosion de projectiles qui partent dans tous les sens.
	// on peux ajouter des projectiles dans "explosion" et les get dans game scene
	// ou dans les projectiles de game scene pour faciliter les collisions.
	for (size_t i = 0; i < 50; i++)
	{
		// TODO
	}
	exploding = true;
}

void Bombe::Draw(RenderWindow &win)
{
	// Pas d'explosion
	if (!exploding)
	{
		Projectile::Draw(win);
	}
	// Avec explosion
	else
	{
		for (size_t i = 0; i < explosion.size(); i++)
		{
			explosion.at(i).Draw(win);
		}
	}
}