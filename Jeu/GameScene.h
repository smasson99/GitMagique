#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Background.h"
#include <string>
#include "Observer.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "DQueue.h"
#include "Projectile.h"
#include "BonusFabric.h"
#include <random>
#include "Stack.h"

using namespace sf;
using namespace std;
using namespace spaceShooter;
using namespace algoPart;

namespace spaceShooter
{ 
    class GameScene :public Scene
	{
	public:
		GameScene();
        ~GameScene();
        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();
        //<smasson>
        void NotifyAShoot(Enemy* shooter);
	private:

        //<smasson>
        void UpdateHUD();

        const int LBL_SPACEMENT = 150;

        Font font;

        int interfaceCommande;

        
        int default = 0;

        //Générateur de nombres aléatoires
        default_random_engine randomEngine;
        //La stack des ennemis
        Stack<int> enemysToCome;
        //Clock pour le spawn des ennemis
        Clock clockEnemys;
        //Timer pour le spawn des ennemis
        Time timerEnemys;
        //La durée minimale pour un spawn
        const float MIN_ENEMYS_SPAWN = 2.5f;
        const float MAX_ENEMYS_SPAWN = 7.5f;


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
        const int NB_BASIC_ENEMYS = 50;
        vector<BasicEnemy*> basicEnemys;
        //
        //</smasson>

		//<sberube>

		Background background;
		BasicEnemy enem;
		BasicEnemy enem2;
		BasicEnemy enem3;

		//</sberube>
	};
}