#pragma once
#include <SFML\Graphics.hpp>
#include <random>
//temp
#include <vector>
using namespace std;
//

using namespace sf;

namespace spaceShooter
{
    //foward declarations
    class Bonus;
	class Projectile;
    class GameScene;

    class Spaceship
    {
    public:
        Spaceship();
        ~Spaceship();
        bool Init(char path[]);
        virtual void Hit(int points);
        void Move(float dirX, float dirY);
        void SetPosition(float x, float y);
        void SetPosition(Vector2f pos);
        virtual void Die();
        void Draw(RenderWindow& mainWin);
        bool IsEnable() const;
        bool IsDead() const;
        void SetEnable(const bool enable);
        Sprite* GetSprite();
        int GetCurrentHealth();
        bool IsPlayer() const;
        virtual void NotifyBonusCollision(Bonus* bonus);
		virtual void NotifyProjectileCollision(Projectile* projectile);
        static void SubscribeToHitByProjectile(GameScene* scene);
        static void CleanUp();
        virtual void Start(Vector2f startPos, default_random_engine& engine);
        virtual int GetCurDamage();
    protected:
        Texture texture;
        Sprite* sprite; //Pointeur, car pas de constructeur par défaut
        float speed;
        int maxHealth, curHealth;
        bool enable;
		bool isPlayer;
        //temp
        static vector<GameScene*> observersHitByProj;
        //
    };
}