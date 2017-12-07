#include "Spaceship.h"
#include "Bonus.h"
#include "Projectile.h"
#include "GameScene.h"
//temp
#include <iostream>
//

vector<GameScene*> Spaceship::observersHitByProj;

spaceShooter::Spaceship::Spaceship()
{
	isPlayer = false;
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
    sprite->setTexture(texture);
    //Ici tout s'est bien passé
    return true;
}

void spaceShooter::Spaceship::Hit(int points)
{
    //Faire perdre le nombre de points de vie
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

bool spaceShooter::Spaceship::IsEnable() const
{
    return enable;
}

bool spaceShooter::Spaceship::IsDead() const
{
    return curHealth <= 0;
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

bool spaceShooter::Spaceship::IsPlayer() const
{
    return this->isPlayer;
}

void spaceShooter::Spaceship::NotifyBonusCollision(Bonus * bonus)
{
}

void spaceShooter::Spaceship::NotifyProjectileCollision(Projectile * projectile)
{
	//Si nous sommes actif et que le projectile est ennemi
	if (this->enable && projectile->GetOwner().isPlayer != isPlayer)
	{
		////debug
		//cout << "Projectile touche (notify spaceship)!" << endl;
        //Notifier les observateurs
        for (GameScene* curScene : observersHitByProj)
        {
            //Recevoir les dégâts
            Hit(projectile->GetDamage());
            //Notifier qu'on est touché
            curScene->NotifyHited(this);
            //Disable du projectile
            projectile->SetEnable(false);
        }
	}
}

void spaceShooter::Spaceship::SubscribeToHitByProjectile(GameScene * subscriber)
{
    //Ajouter l'observateur
    observersHitByProj.push_back(subscriber);
}

void spaceShooter::Spaceship::CleanUp()
{
    //CleanUp des vecteurs
    for (GameScene* curScene : observersHitByProj)
    {
        curScene = nullptr;
    }
    observersHitByProj.clear();
}

void spaceShooter::Spaceship::Start(Vector2f startPos, default_random_engine & engine)
{
    this->sprite->setPosition(startPos);
    this->enable = true;
}

int spaceShooter::Spaceship::GetCurDamage()
{
    return 1;
}
