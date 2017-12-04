#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

namespace spaceShooter
{
    //foward declaration
    class Bonus;

    class Spaceship
    {
    public:
        Spaceship();
        ~Spaceship();
        bool Init(char path[]);
        virtual void Hit(int points);
       // virtual void Notify(Subject* subject)=0;
        void Move(float dirX, float dirY);
        void SetPosition(float x, float y);
        void SetPosition(Vector2f pos);
        virtual void Die();
        void Draw(RenderWindow& mainWin);
        bool IsEnable();
        void SetEnable(const bool enable);
        Sprite* GetSprite();
        int GetCurrentHealth();
        virtual void NotifyBonusCollision(Bonus* bonus);
    protected:
        Texture texture;
        Sprite* sprite; //Pointeur, car pas de constructeur par défaut
        float speed;
        int maxHealth, curHealth;
        bool enable;
    };
}