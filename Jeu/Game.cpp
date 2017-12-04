#include "Game.h"
#include "Scene.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "EndScreen.h"
#include "Observer.h"
using namespace spaceShooter;

Game::Game()
{
    //On place dans le contructeur ce qui permet à la game elle-même de fonctionner
    setlocale(LC_ALL, "");
    mainWin.create(VideoMode(LARGEUR, HAUTEUR, 32), "Space Shooter", Style::Titlebar);  // , Style::Titlebar); / , Style::FullScreen);

                                                                    //Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
    mainWin.setVerticalSyncEnabled(true);
    //mainWin.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
    //https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

spaceShooter::Game::~Game()
{
    mainWin.close();
}

int Game::testTest()
{
    return 0;
}

int Game::run()
{
    //deux enums et un pointeur de scene pour faire la manipulation de scène
    Scene::scenes selecteurDeScene = Scene::scenes::MAIN_MENU;
    //Scene::scenes selecteurDeScene = Scene::scenes::GESTION_COMPTE;
    Scene::scenes sceneEnRetour;
    Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle scène

    while (true)
    {
        //Seule condition de sortie de toute l'app
        if (selecteurDeScene == Scene::scenes::EXIT)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            //Vous allez ajouter d'autre scènes, alors elles devront
            //être ajoutées ici
            switch (selecteurDeScene)
            {
                // <smasson>
            case Scene::scenes::MAIN_MENU:
                sceneActive = new MainMenu();
                break;
            case Scene::scenes::GAME:
                sceneActive = new GameScene();
                break;
			case Scene::scenes::END_GAME:
				sceneActive = new EndScreen();
				break;
            }

            if (sceneActive->init(&mainWin))
            {
                sceneEnRetour = sceneActive->run();
                //À la fin d'une scène, s'il y a des sauvegardes à faire
                //C'est aussi possible de les faire là.
            }
            else
            {
                //cleap-up à faire pour s'assurer  de ne pas avoir de leak
                //(malgré l'échec)
                return EXIT_FAILURE;
            }
        }

        selecteurDeScene = sceneEnRetour;
        delete sceneActive;
        sceneActive = nullptr;
    }
}

bool Game::init()
{
    return true;
}