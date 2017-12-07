#include "GameScene.h"
#include "GameStyle.h"
#include "ProjectileGenerator.h"
#include "GlobalMath.h"
//Debug
#include <iostream>
//

GameScene::GameScene()
{
    //Déclaration des variables
    player = Player::GetInstance();
}

GameScene::~GameScene()
{
    //Clean-up
    //temp
    //Clear des vecteurs
    for (Projectile* curProj : basicProjectiles)
        delete curProj;
    for (Bonus* curBonus : scoresBonus)
        delete curBonus;
    for (BasicEnemy* curEnem : basicEnemys)
        delete curEnem;
    basicProjectiles.clear();
    scoresBonus.clear();
    basicEnemys.clear();
    //
    //Destruction du joueur
    player->KillInstance();
    //Clean-up statiques
    Bonus::CleanUp();
    Enemy::CleanUp();
    Spaceship::CleanUp();
    Projectile::CleanUp();
    BasicEnemy::CleanUp();
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
    enem.SetPosition(500, 10);
    enem2.SetPosition(400, 10);
    enem3.SetPosition(600, 10);
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

    //<smasson>
    //Initialisation des variables par défaut
    ResetEnemysTimer();
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

    //Initialisation des ennemis et du contenu lié aux ennemis
#pragma region:Enemys&ContentInit
    //Ennemis
    //Ennemis Basiques
    for (int i = 0; i < NB_BASIC_ENEMYS; ++i)
    {
        //Push d'un ennemi
        basicEnemys.push_back(new BasicEnemy());
        //Init de l'ennemi en question
        basicEnemys.at(i)->AdjustVisual();
    }
    //Contenu
    //Déclaration des variables
    uniform_int_distribution<int> distributionEnemys(0, Enemy::EnemyType::MAX_ENEMYS - 1);
    int lastKamikaze = 0;
    int lastReflector = 0;
    int lastQueen = 0;
    int lastBoss = 0;
    bool ok = false;
    int res = 0;
    for (int i = 0; i < 1000; ++i)
    {
        while (ok == false)
        {
            res = distributionEnemys(randomEngine);
            switch (res)
            {
            case Enemy::EnemyType::BASIC:
                //Les ennemis basiques sont toujours les bienvenus!
                ok = true;
                break;
            case Enemy::EnemyType::KAMIKAZE:
                //Si nous débutons ou que nous avons au moins 4 ennemis entre le dernier kamikaze et la position actuelle, alors
                if (lastKamikaze + 5 <= i || lastKamikaze == 0)
                {
                    lastKamikaze = i;
                    ok = true;
                }
                break;
            case Enemy::EnemyType::REFLECTOR:
                //Si nous débutons ou que nous avons au moins 6 ennemis entre le dernier reflector et la position actuelle, alors
                if (lastReflector + 7 <= i || lastReflector == 0)
                {
                    lastReflector = i;
                    ok = true;
                }
                break;
            case Enemy::EnemyType::QUEEN:
                //Si nous avons au moins 12 ennemis entre la dernière reine et la position actuelle, alors
                if (lastQueen + 13 <= i)
                {
                    lastQueen = i;
                    ok = true;
                }
                break;
            case Enemy::EnemyType::BOSS_CANNON:
                //Si nous avons au moins 35 ennemis entre le dernier Boss et la position actuelle, alors
                if (lastBoss + 36 <= i)
                {
                    lastBoss = i;
                    ok = true;
                }
                break;
            }
        }
        enemysToCome.Push(res);
        ok = false;
    }
#pragma endregion

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
    //Joueur collide avec projectile
    Projectile::SubscribeToCollisions(player);
    //Ennemis collident avec projetile (abonnement)
    for (BasicEnemy* curEnemy : basicEnemys)
        Projectile::SubscribeToCollisions(curEnemy);
    Spaceship::SubscribeToHitByProjectile(this);
    //</smasson>
#pragma endregion

    //Ici, l'init est un succès, retourner true
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
                    curProj->Start(player->GetDirection(), player->GetSprite()->getPosition(), *player);
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
            }
        }
    }
    //</smasson>
#pragma endregion
    //Update des ennemis
#pragma region:EnemysUpdate
    //Update des ennemis basiques actifs
    for (BasicEnemy* curEnemy : basicEnemys)
    {
        if (curEnemy->IsEnable())
        {
            curEnemy->Update(player->GetSprite()->getPosition());
        }
    }
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
    //Dessiner les personnages
    for (BasicEnemy* curEnemy : basicEnemys)
    {
        if (curEnemy->IsEnable())
        {
            curEnemy->Draw(*mainWin);
        }
    }
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

//<smasson>

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
                curProj->Start(shooter->GetDir(), shooter->GetSprite()->getPosition(), *shooter);
                break;
            }
        }
        break;
    }
}

void spaceShooter::GameScene::NotifyHited(Spaceship * victim)
{
}

bool spaceShooter::GameScene::CanSpawnEnemys()
{
    return clockEnemys.getElapsedTime().asSeconds() >= timerEnemys.asSeconds();
}

void spaceShooter::GameScene::SpawnEnemy(int type)
{
    switch (type)
    {
    case Enemy::EnemyType::BASIC:
        cout << "Basic spawn!" << endl;
        //Trouver un ennemi disable
        for (BasicEnemy* curEnem : basicEnemys)
        {
            if (!curEnem->IsEnable())
            {
                //Random
                uniform_int_distribution<int> distribution(Background::LeftLimit() + curEnem->GetSprite()->getGlobalBounds().width / 2, Background::RightLimit() - curEnem->GetSprite()->getGlobalBounds().width / 2);
                //Start à une position aléatoire
                curEnem->Start(Vector2f(distribution(randomEngine), -50), randomEngine);
                //Nous l'avons trouvé, break
                break;
            }
        }
        break;
    case Enemy::EnemyType::KAMIKAZE:
        cout << "Kamikaze spawn!" << endl;
        break;
    case Enemy::EnemyType::REFLECTOR:
        cout << "Reflector spawn!" << endl;
        break;
    case Enemy::EnemyType::QUEEN:
        cout << "Queen spawn!" << endl;
        break;
    case Enemy::EnemyType::BOSS_CANNON:
        cout << "Boss spawn!" << endl;
        break;
    }
}

void spaceShooter::GameScene::ResetEnemysTimer()
{
    uniform_real_distribution<float> distribution(MIN_ENEMYS_SPAWN, MAX_ENEMYS_SPAWN);
    timerEnemys = seconds(distribution(randomEngine));
}

int spaceShooter::GameScene::GetScoreFromKill(Enemy::EnemyType victimType)
{
    switch (victimType)
    {
    case Enemy::EnemyType::BASIC:
        return 100;
        break;
    case Enemy::EnemyType::KAMIKAZE:
        return 150;
        break;
    case Enemy::EnemyType::REFLECTOR:
        return 250;
        break;
    case Enemy::EnemyType::QUEEN:
        return 500;
        break;
    case Enemy::EnemyType::BOSS_CANNON:
        return 1000;
        break;
    }
}

void spaceShooter::GameScene::SpawnBonus(Bonus::BonusType type, Vector2f pos)
{
    //Faire spawner un bonus selon le type
    switch (type)
    {
    case Bonus::BonusType::ScoreBonus_Type:
        //Spawn d'un bonus de type score
        for (Bonus* curBonus : scoresBonus)
        {
            if (curBonus->IsEnable())
            {
                curBonus->Start(pos);
                curBonus->Disable();
            }
        }
        break;
    }
}

void spaceShooter::GameScene::SpawnBonusFromEnemyType(Enemy::EnemyType type, Vector2f pos)
{
    //D'abord, si nous ne sommes pas de type boss
    if (type != Enemy::EnemyType::BOSS_CANNON)
    {

    }
    //Sinon, nous sommes de type boss, alors
    else
    {
        //Spawn d'un bonus aléatoire, car c'est un boss
        uniform_int_distribution<int> bonusRand(0, Bonus::BonusType::BonusType_MAX-1);

        //Selon le type de bonus, spawner
        switch (bonusRand(randomEngine))
        {
        case Bonus::BonusType::ScoreBonus_Type:
            //Spawn d'un bonus de score
            break;
        }
    }
    switch (type)
    {
    case Enemy::EnemyType::BASIC:
        break;
    case Enemy::EnemyType::KAMIKAZE:
        break;
    case Enemy::EnemyType::REFLECTOR:
        break;
    case Enemy::EnemyType::QUEEN:
        break;
    case Enemy::EnemyType::BOSS_CANNON:
        break;
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
//</smasson>