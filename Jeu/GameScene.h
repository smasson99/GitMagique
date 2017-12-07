#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Background.h"
#include <string>
#include "Observer.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "DQueue.h"
#include "BonusFabric.h"
#include "Kamikaze.h"
using namespace sf;

namespace spaceShooter
{ 
    class GameScene :public Scene, public Observer
	{
	public:
		GameScene();
        ~GameScene();
        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();
        void Notify(Subject* subject);
        void NotifyAShoot(Enemy* shooter);
		void NotifyAnExplosion(Bombe* bomb);
        void NotifyHited(Spaceship* victim);
        bool CanSpawnEnemys();
        void SpawnEnemy(int type);
        void ResetEnemysTimer();
        int GetScoreFromKill(Enemy::EnemyType victimType);
        void SpawnBonus(Bonus::BonusType type, Vector2f pos);
        void SpawnBonusFromEnemyType(Enemy::EnemyType type, Vector2f pos);
        //</smasson>
	private:

        //<smasson>
        void UpdateHUD();

        const int LBL_SPACEMENT = 150;

        Font font;

        int interfaceCommande;

        int default = 0;
        //Labels de statistiques
        Text scoreMultiplicatorLabel;
        Text currentScoreLabel;
        Text lifesLabel;
        Text shieldLabel;
        Text curWeaponLabel;
        Text munitionsLabel;
        Text nextEnemyLabel;
        
        Player* player;

        //Les chances de drop
        const int PERCENT_DROP_SCORE_BONUS = 15;

        //temp
        const int NB_BASIC_PROJECTILES = 250;
        vector<Projectile*> basicProjectiles;
        const int NB_SCORE_BONUS = 25;
        vector<Bonus*> scoresBonus;
        //
        //</smasson>

		//<sberube>

		Background background;
		const int nbProjExplosion = 200;
		const int nbProjWhenExpl = 12;
		vector<BombProj*> explosion;
		const int nbBombsStart = 50;
		int nbBombs = 5;
		vector<Bombe*> bombs;

		Time bombTime = seconds(3);
		Clock bombTimer;

		//<Tests>
		//BasicEnemy enem;
		//BasicEnemy enem2;
		//BasicEnemy enem3;
		//Kamikaze enem4;
		//Bombe *bomb;

		//</sberube>
	};
}