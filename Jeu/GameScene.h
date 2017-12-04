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
		BasicEnemy enem;
		BasicEnemy enem2;
		BasicEnemy enem3;

		//</sberube>
	};
}