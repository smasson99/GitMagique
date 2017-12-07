#include "Spaceship.h"
#include "Bonus.h"

spaceShooter::Spaceship::Spaceship()
{
    sprite = new Sprite();
    speed = 2.5f;
    maxHealth = 1;
    curHealth = maxHealth;
    enable = false;
}

spaceShooter::Spaceship::~Spaceship()
{
    delete sprite;
    sprite = nullptr;
}

bool spaceShooter::Spaceship::Init(char path[])
{
    //Loader la texture
    if (!texture.loadFromFile(path))
        return false;
	sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite->setTexture(texture);
    //Ici tout s'est bien passé
    return true;
}

void spaceShooter::Spaceship::Hit(int points)
{
    //Faire perdre de la vie au joueur
    curHealth -= points;
}

void spaceShooter::Spaceship::Move(float dirX, float dirY)
{
    sprite->move(dirX*speed, dirY*speed);
}

void spaceShooter::Spaceship::SetPosition(float x, float y)
{
    sprite->setPosition(x, y);
}

void spaceShooter::Spaceship::SetPosition(Vector2f pos)
{
    sprite->setPosition(pos);
}

void spaceShooter::Spaceship::Die()
{
    curHealth = 0;
    enable = false;
}

void spaceShooter::Spaceship::Draw(RenderWindow & mainWin)
{
    mainWin.draw(*sprite);
}

bool spaceShooter::Spaceship::IsEnable()
{
    return enable;
}

void spaceShooter::Spaceship::SetEnable(const bool enable)
{
    this->enable = enable;
}

Sprite * spaceShooter::Spaceship::GetSprite()
{
    return sprite;
}

int spaceShooter::Spaceship::GetCurrentHealth()
{
    return curHealth;
}

void spaceShooter::Spaceship::NotifyBonusCollision(Bonus * bonus)
{
}
