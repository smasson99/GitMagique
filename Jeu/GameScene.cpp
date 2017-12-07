#include "GameScene.h"
#include "GameStyle.h"
#include "ProjectileGenerator.h"
#include "GlobalMath.h"
//Debug
#include <iostream>
using namespace std;
//

using namespace spaceShooter;

GameScene::GameScene()
{
    //Déclaration des variables
    player = Player::GetInstance();
}

GameScene::~GameScene()
{
    //Clean-up
    //Clear des vecteurs
    for (Projectile* curProj : basicProjectiles)
        delete curProj;
    for (Bonus* curBonus : scoresBonus)
        delete curBonus;
	for (Bombe* curBomb : bombs)
		delete curBomb;
	for (BombProj* curBombProj : explosion)
		delete curBombProj;

    basicProjectiles.clear();
    scoresBonus.clear();
	bombs.clear();
	explosion.clear();
    //Destruction du joueur
    player->KillInstance();
    //Clean-up statiques
    Bonus::CleanUp();
    Enemy::CleanUp();
    //Clean up adresses
    player = nullptr;
}

Scene::scenes GameScene::run()
{

    while (isRunning)
    {
        getInputs();
        update();
        draw();
    }

    return transitionVersScene;
}

bool GameScene::init(RenderWindow * const window)
{
 //   enem.SetPosition(500, -10);
 //   enem.Init("");
 //   enem2.SetPosition(400, -10);
 //   enem2.Init("");
 //   enem3.SetPosition(600, -10);
 //   enem3.Init("");
	//enem4.Init("Ressources\\Textures\\Actors\\Ship.png");
	//enem4.SetPosition(800, -10);
    if (!background.Init(*window))
    {
        return false;
    }
    // <smasson>
    /*if (!ambianceMusic.openFromFile("Ressources\\Sounds\\Music.ogg"))
    {
    return false;
    }*/
    //Init du font:
    if (!font.loadFromFile("Ressources\\Fonts\\STJEDISE.ttf"))
        return false;
    //</smasson>

#pragma region:textureLoad
    if (!ScoreBonus::Init("Ressources\\Textures\\Other\\Multiplicator.png"))
        return false;
    if (!Player::Init("Ressources\\Textures\\Actors\\Ship.png"))
        return false;
    if (!BasicEnemy::Init("Ressources\\Textures\\Actors\\Ship.png"))
        return false;
#pragma endregion

#pragma region HUD
    //<smasson>
    //Initialisation du HUD
    //Le multiplicateur de score:
    scoreMultiplicatorLabel.setFont(font);
    scoreMultiplicatorLabel.setCharacterSize(GameStyle::inGameFontSize);
    scoreMultiplicatorLabel.setFillColor(GameStyle::gameFontColor);
    scoreMultiplicatorLabel.setPosition(window->getSize().x - 265, window->getSize().y - 700);

    //Le score courant:
    currentScoreLabel.setFont(font);
    currentScoreLabel.setCharacterSize(GameStyle::inGameFontSize);
    currentScoreLabel.setFillColor(GameStyle::gameFontColor);
    currentScoreLabel.setPosition(window->getSize().x - 265, window->getSize().y - 700 + LBL_SPACEMENT);

    //Le prochain ennemi à apparaître:
    nextEnemyLabel.setFont(font);
    nextEnemyLabel.setCharacterSize(GameStyle::inGameFontSize);
    nextEnemyLabel.setFillColor(GameStyle::gameFontColor);
    nextEnemyLabel.setPosition(window->getSize().x - 265, window->getSize().y - 700 + LBL_SPACEMENT * 2);

    //Le nombre de points de vie du joueur
    lifesLabel.setFont(font);
    lifesLabel.setCharacterSize(GameStyle::inGameFontSize);
    lifesLabel.setFillColor(GameStyle::gameRedColor);
    lifesLabel.setPosition(10, window->getSize().y - 700);

    //Le nombre de points de vie du shield courant du joueur
    shieldLabel.setFont(font);
    shieldLabel.setCharacterSize(GameStyle::inGameFontSize);
    shieldLabel.setFillColor(GameStyle::gameRedColor);
    shieldLabel.setPosition(10, window->getSize().y - 700 + LBL_SPACEMENT);

    //L'arme courante du joueur
    curWeaponLabel.setFont(font);
    curWeaponLabel.setCharacterSize(GameStyle::inGameFontSize);
    curWeaponLabel.setFillColor(GameStyle::gameRedColor);
    curWeaponLabel.setPosition(10, window->getSize().y - 700 + LBL_SPACEMENT * 2);

    //Le nombre du munitions de l'arme du joueur
    munitionsLabel.setFont(font);
    munitionsLabel.setCharacterSize(GameStyle::inGameFontSize);
    munitionsLabel.setFillColor(GameStyle::gameRedColor);
    munitionsLabel.setPosition(10, window->getSize().y - 700 + LBL_SPACEMENT * 3);
    // </smasson>
#pragma endregion
    //ambianceMusic.setLoop(true);
    //ambianceMusic.setVolume(100);
    //ambianceMusic.play();

    //Initialisation des projectiles
#pragma region:ProjectileInit
    for (int i = 0; i < NB_BASIC_PROJECTILES; ++i)
    {
        basicProjectiles.push_back(ProjectileGenerator::GetProjectile(Projectile::ProjectileType::BASIC));
    }
	for (size_t i = 0; i < nbProjExplosion; i++)
	{
		explosion.push_back((BombProj*)ProjectileGenerator::GetProjectile(Projectile::ProjectileType::BOMB_PROJ));
	}
	for (size_t i = 0; i < nbBombsStart; i++)
	{
		bombs.push_back((Bombe*)ProjectileGenerator::GetProjectile(Projectile::ProjectileType::BOMB));
	}
#pragma endregion

    //Initialisation des bonus
#pragma region:BonusInit
    for (int i = 0; i < NB_SCORE_BONUS; ++i)
    {
        scoresBonus.push_back(BonusFabric::GetBonus(Bonus::BonusType::ScoreBonus_Type));
    }
#pragma endregion

    //Initialisation du random time
    srand(time(NULL));

    //<smasson>
    //temp
    //enem.AdjustVisual();
    //enem2.AdjustVisual();
    //enem3.AdjustVisual();
    //

    //Initialisation du joueur
    player->AdjustVisual();
    player->SetPosition(window->getSize().x / 2, window->getSize().y / 2);
    player->SetLimits(Vector2f(Background::LeftLimit(), 350),
    Vector2f(Background::RightLimit(), Background::WinHeight()));
    //</smasson>
    this->mainWin = window;
    isRunning = true;

#pragma region:SubscribeZone
    //<smasson>
    Bonus::SubscribeToCollisions(player);
    BasicEnemy::SubscribeToShoots(this);
	Bombe::SubExplosion(this);
    //</smasson>
#pragma endregion
    return true;
}

void GameScene::getInputs()
{
    while (mainWin->pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == Event::Closed)
        {
            //Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
            //fin à l'application
            isRunning = false;
            transitionVersScene = Scene::scenes::EXIT;
        }

        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                isRunning = false;
                transitionVersScene = Scene::scenes::MAIN_MENU;
            }
        }
    }

    interfaceCommande = 0;
    //<smasson>
    //Méthode binaire: appuyer à gauche et à droite sumultanément va donner 3, et le personnage ne se dépalcera alors pas.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        interfaceCommande |= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        interfaceCommande |= 2;
		for (size_t i = 0; i < bombs.size(); i++)
		{
			bombs.at(i)->Explode();
		}
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        interfaceCommande |= 4;
        background.SetSpeed(4);
    }
    else
    {
        background.SetSpeed(2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        interfaceCommande |= 8;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        interfaceCommande |= 16;
		if (nbBombs > 0 && bombTimer.getElapsedTime().asMilliseconds() > bombTime.asMilliseconds())
		{
			bombTimer.restart();
			for (Bombe* curBomb : bombs)
			{
				if (!curBomb->IsEnable())
				{
					curBomb->Start(player->GetDirection(), player->GetSprite()->getPosition());
					
				}
			}
			nbBombs--;
		}
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        interfaceCommande |= 32;
    }
    if (sf::Mouse::isButtonPressed(Mouse::Left))
    {
        //Énénement direct de tirs du joueur
        //Si le joueur peut tirer
        if (player->CanShoot())
        {
            //Tirer
            player->Shoot();
            //Ajouter le projectile au jeu
            for (Projectile* curProj : basicProjectiles)
            {
                //Si le projectile est inactif
                if (!curProj->IsEnable())
                {
                    curProj->Start(player->GetDirection(), player->GetSprite()->getPosition());
                    //On break, car nous avons trouvé notre projectile
                    break;
                }
            }
        }
    }
    //</smasson>
}

void GameScene::update()
{
    //Updater le background
    background.Update(*mainWin);

    //Updater les projectiles
#pragma region:ProjectilesUpdate
    //Projectiles basiques
    for (Projectile* curProj : basicProjectiles)
    {
        //Si le projectile courant est actif, alors
        if (curProj->IsEnable())
        {
            //Updater ce projectile
            curProj->Update();
            //Si le projectile sort des limites de l'écran
            if (GlobalMath::IsOutOfScreen(curProj->GetPosition()))
            {
                //Rendre le projectile inactif
                curProj->SetEnable(false);
                //cout << "Sortie d'un projectile." << endl;
            }
        }
    }
	// Bombes
	for (size_t i = 0; i < bombs.size(); i++)
	{
		// Si la bombe est en jeu
		if (bombs.at(i)->IsEnable())
		{
			// On l'update
			bombs.at(i)->Update();
		}
		// sortie de l'écran
		if (GlobalMath::IsOutOfScreen(bombs.at(i)->GetPosition()))
		{
			//Rendre la bombe inactive
			bombs.at(i)->SetEnable(false);

		}
	}
	// Projectiles de l'explosion de la bombe
	for (size_t i = 0; i < nbProjExplosion; i++)
	{
		// Si la bombe est en jeu
		if (explosion.at(i)->IsEnable())
		{
			// On l'update
			explosion.at(i)->Update();
		}
		// sortie de l'écran
		if (GlobalMath::IsOutOfScreen(explosion.at(i)->GetPosition()))
		{
			//Rendre la bombe inactive
			explosion.at(i)->SetEnable(false);
		}
		
	}
#pragma endregion
    //Update des bonus
#pragma region:BonusUpdate
    //<smasson>
    //Bonus de score
    for (Bonus* curBonus : scoresBonus)
    {
        //Si le bonus est actif
        if (curBonus->IsEnable())
        {
            //Updater ce bonus
            curBonus->Update();
            //Si ce bonus est hors de l'écran de jeu
            if (GlobalMath::IsOutOfScreen(curBonus->GetPos()))
            {
                //Rendre le bonus inactif
                curBonus->Disable();
                //cout << "Sortie d'un bonus de score." << endl;
            }
        }
    }
    //</smasson>
#pragma endregion
    //Update du joueur
    player->Update(interfaceCommande);

    //Updater le HUD
    UpdateHUD();

 //   enem.Update(Vector2f(player->GetSprite()->getPosition()));
 //   enem2.Update(Vector2f(player->GetSprite()->getPosition()));
 //   enem3.Update(Vector2f(player->GetSprite()->getPosition()));
	//enem4.Update(Vector2f(player->GetSprite()->getPosition()));
	//bomb->Update();
}

void GameScene::draw()
{
    //Toujours important d'effacer l'écran précédent
    mainWin->clear();
    //Dessiner background
    background.Draw(*mainWin);
    //Dessiner contenu
    //Dessiner les projectiles
    //Projectiles basiques
    for (Projectile* curProj : basicProjectiles)
    {
        //Si le projectile est actif
        if (curProj->IsEnable())
        {
            //Dessiner le projectile
            curProj->Draw(*mainWin);
        }
    }
    //Dessiner les bonus
    for (Bonus* curBonus : scoresBonus)
    {
        //Si le bonus est actif
        if (curBonus->IsEnable())
        {
            //Dessiner le bonus
            curBonus->Draw(*mainWin);
        }
    }
	// Bombes
	for (size_t i = 0; i < bombs.size(); i++)
	{
		// Si la bombe est en jeu
		if (bombs.at(i)->IsEnable())
		{
			// On la dessine
			bombs.at(i)->Draw(*mainWin);
		}
	}
	// Projectiles de l'explosion de la bombe
	for (size_t i = 0; i < nbProjExplosion; i++)
	{
		// Si le projectile est en jeu
		if (explosion.at(i)->IsEnable())
		{
			// On le dessine
			explosion.at(i)->Draw(*mainWin);
		}
	}
    //Dessiner les personnages
 //   enem.Draw(*mainWin);
 //   enem2.Draw(*mainWin);
 //   enem3.Draw(*mainWin);
	//enem4.Draw(*mainWin);
    //Le joueur
    player->Draw(*mainWin);
    //<smasson>
    //Dessiner le HUD
    mainWin->draw(scoreMultiplicatorLabel);
    mainWin->draw(currentScoreLabel);
    mainWin->draw(lifesLabel);
    mainWin->draw(shieldLabel);
    mainWin->draw(curWeaponLabel);
    mainWin->draw(munitionsLabel);
    mainWin->draw(nextEnemyLabel);
    //</smasson>
    //Afficher la nouvelle écran
    mainWin->display();
}

void GameScene::Notify(Subject * subject)
{
}

void spaceShooter::GameScene::NotifyAShoot(Enemy* shooter)
{
    //Tirer un projectile du type de celui de l'ennemi
    switch (shooter->GetProjectileType())
    {
    case Projectile::ProjectileType::BASIC:
        //On ajoute un projectile!
        for (Projectile* curProj : basicProjectiles)
        {
            if (!curProj->IsEnable())
            {
                curProj->Start(shooter->GetDir(), shooter->GetSprite()->getPosition());
                break;
            }
        }
        break;
	case Projectile::ProjectileType::BOMB:
		// On ajoute une bombe
		for (Bombe* curBomb : bombs)
		{
			if (!curBomb->IsEnable())
			{
				curBomb->Start(shooter->GetDir(), shooter->GetSprite()->getPosition());
			}
		}
    }
}
void spaceShooter::GameScene::NotifyAnExplosion(Bombe* bombe)
{
	int projCount = 0;
	//On ajoute les projectiles de L'EXPLOOOSION!
	for (size_t i = 0; i < explosion.size(); i++)
	{
		int rdn = rand() % 2 + 1;
		if (!explosion.at(i)->IsEnable())
		{
			explosion.at(i)->SetRotation(360 / nbProjExplosion * i);
			if (projCount % 2 == 0)
			{
				explosion.at(i)->Start(Vector2f(cosf(360 / nbProjExplosion * i * 2), sinf(360 / nbProjExplosion * i * 2)), bombe->GetPosition());
			}
			projCount++;
		}
		if (projCount == nbProjWhenExpl)
		{
			break;
		}
	}
}
void spaceShooter::GameScene::UpdateHUD()
{
    //<smasson>
    //Le multiplicateur de score
    scoreMultiplicatorLabel.setString("Score Bonus: \n" + std::to_string(player->GetScoreMultiplicatorValue()));
    //Le score courant
    currentScoreLabel.setString("Score: \n" + std::to_string(player->GetScore()));
    //Le nombre de points de vie restants
    int playerHealthPoints;
    lifesLabel.setString("Health Points: \n" + std::to_string(default));
    shieldLabel.setString("Shield Lifes: \n" + std::to_string(default));
    //L'arme courante du joueur
    string curWepName = "";
    switch (player->GetWeaponType())
    {
    case Weapon::BASIC_WEAPON:
        curWepName = "Lazers";
        break;
    default:
        curWepName = "default";
        break;
    }
    curWeaponLabel.setString("Weapon: \n" + curWepName);

    //Le nombre de munitions du joueur
    string munitions = "Unlimited";
    if (player->GetWeaponType() != Weapon::WeaponType::BASIC_WEAPON)
        munitions = std::to_string(player->GetNbMunitions());
    munitionsLabel.setString("Shoots Left: \n" + munitions);
    nextEnemyLabel.setString("Next Enemy: \n" + std::to_string(default));
    //</smasson>
}
