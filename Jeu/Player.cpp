#include "Player.h"
#include "GlobalMath.h"
#include "WeaponGenerator.h"
#include "GameScene.h"

using namespace spaceShooter;

Player* Player::instance = nullptr;
Texture Player::texture;


Player::Player() :Spaceship()
{
    //Ajout de l'arme basique du joueur
    weapons.push_back(WeaponGenerator::GetWeapon(Weapon::WeaponType::BASIC_WEAPON));
    curWepIndex = 0;
    curScorMult = 1;
    score = 0;
    this->maxHealth = 40;
    this->curHealth = maxHealth;
}

Player::~Player()
{
    for (Weapon* curWeapon : weapons)
    {
        delete curWeapon;
    }
    weapons.clear();
}

Player * Player::GetInstance()
{
    if (instance == nullptr)
        instance = new Player();
    return instance;
}

void Player::KillInstance()
{
    delete instance;
    instance = nullptr;
}

void Player::SetLimits(const Vector2f point1, const Vector2f point2)
{
    limitMin = Vector2f(point1.x + sprite->getTexture()->getSize().x / (2 / (sprite->getScale().x)), point1.y - sprite->getTexture()->getSize().y/16 /*/ (2 * (sprite->getScale().y))*/);
    limitMax = Vector2f(point2.x - sprite->getTexture()->getSize().x / (2 / (sprite->getScale().x)), point2.y - sprite->getTexture()->getSize().y / (14 * (sprite->getScale().y)));
}

void Player::Notify(Subject * subject)
{

}

bool Player::Update(int commands)
{
    Vector2f dir(0, 0);

    //gauche
    if (commands & 1)
    {
        dir.x = -1;
    }
    //droite
    else if (commands & 2)
    {
        dir.x = 1;
    }
    //haut
    if (commands & 4)
    {
        dir.y = -1;
    }
    //bas
    else if (commands & 8)
    {
        dir.y = 1;
    }

    //Bouger
    Move(dir.x, dir.y);
    //Vérifier limites
    sprite->setPosition(GlobalMath::InspectPos(sprite->getPosition(), limitMin, limitMax));

    if (commands == 16)
    {
        // On demande au jeu de tirer une bombe.
    }
    if (commands == 32)
    {
        //q, pour les changements d'armes
    }

    return curHealth >= 0;
}

bool spaceShooter::Player::CanShoot()
{
    return weapons.at(curWepIndex)->CanShoot();
}

void spaceShooter::Player::Shoot()
{
    weapons.at(curWepIndex)->Shoot();
}

Vector2f spaceShooter::Player::GetDirection()
{
    return Vector2f(0, -1);
}

Weapon::WeaponType spaceShooter::Player::GetWeaponType()
{
    return weapons.at(curWepIndex)->GetType();
}

int spaceShooter::Player::GetNbMunitions()
{
    return weapons.at(curWepIndex)->GetNbProjs();
}

int spaceShooter::Player::GetScoreMultiplicatorValue()
{
    return curScorMult;
}

void spaceShooter::Player::AddScore(int points)
{
    score += (points*curScorMult);
}

int spaceShooter::Player::GetScore()
{
    return score;
}

bool spaceShooter::Player::Init(char path[])
{
    if (!texture.loadFromFile(path))
        return false;
    return true;
}

void spaceShooter::Player::AdjustVisual()
{
    sprite->setTexture(texture);
    sprite->setScale(0.4f, 0.4f);
    sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
