#include "Projectile.h"

vector<Spaceship*> Projectile::observersCollisions;

spaceShooter::Projectile::Projectile(const float x, const float y, const Color color, const float speed, Spaceship * owner) :speed(speed), owner(owner)
{
    shape = new RectangleShape();
    RectangleShape* curShape = (RectangleShape*)shape;
    curShape->setSize(Vector2f(x, y));
    curShape->setOrigin(curShape->getSize().x / 2, curShape->getSize().y / 2);
    curShape->setFillColor(color);
    curShape = nullptr;
    delete curShape;
    isEnable = false;
    this->damage = owner->GetCurDamage();
}

spaceShooter::Projectile::~Projectile()
{
    //Clean-up
    delete shape;
    owner = nullptr;
    shape = nullptr;
}

void spaceShooter::Projectile::Start(const Vector2f dir, Vector2f position, Spaceship& owner)
{
    this->dir = dir;
    shape->setPosition(position);
    this->owner = &owner;
    this->damage = owner.GetCurDamage();
    isEnable = true;
}

void spaceShooter::Projectile::SetTexture(const Texture& texture)
{
    shape->setTexture(&texture);
}

void spaceShooter::Projectile::Draw(RenderWindow & mainWin)
{
    mainWin.draw(*shape);
}

void spaceShooter::Projectile::SetOwner(Spaceship & newOwner)
{
    this->owner = &newOwner;
    this->damage = newOwner.GetCurDamage();
}

Color spaceShooter::Projectile::GetColor()
{
    return shape->getFillColor();
}

Spaceship & spaceShooter::Projectile::GetOwner()
{
    return *this->owner;
}

void spaceShooter::Projectile::Update()
{
    //Avancer le projectile dans la direction à sa vitesse
    shape->move(dir.x*speed, dir.y*speed);
    //Vérifier les collisions
    //Pour chaque observateur
	for (Spaceship* curObserver : observersCollisions)
	{
		if (shape->getGlobalBounds().intersects(curObserver->GetSprite()->getGlobalBounds()))
		{
			//Avertir l'observateur
            curObserver->NotifyProjectileCollision(this);
		}
	}
}

bool spaceShooter::Projectile::IsEnable()
{
    return this->isEnable;
}

void spaceShooter::Projectile::SetEnable(bool enable)
{
    this->isEnable = enable;
}

Vector2f spaceShooter::Projectile::GetPosition()
{
    return shape->getPosition();
}

void spaceShooter::Projectile::SubscribeToCollisions(Spaceship * subscriber)
{
	//Ajouter un abonné pour les collisions
	observersCollisions.push_back(subscriber);
}

void spaceShooter::Projectile::CleanUp()
{
	//Clean-Up!
	for (Spaceship* curObserver : observersCollisions)
	{
		curObserver = nullptr;
	}
	observersCollisions.clear();
}

int spaceShooter::Projectile::GetDamage() const
{
    return this->damage;
}
