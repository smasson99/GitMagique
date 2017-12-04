#include "MainMenu.h"
#include "GameStyle.h"

using namespace spaceShooter;

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{
    currentButton = nullptr;
    delete currentButton;
}

Scene::scenes MainMenu::run()
{
    while (isRunning)
    {
        getInputs();
        update();
        draw();
    }

    return transitionVersScene;
}

bool MainMenu::init(RenderWindow * const window)
{

    if (!font.loadFromFile("Ressources\\Fonts\\STJEDISE.ttf"))
    {
        return false;
    }

    ecranTitre.setTexture(ecranTitreT);

    //Les positions sont arbitraires, obtenus par essai et erreur.
    //par rapport au fond d'écran
    buttonPlay.init(500, 15, Vector2f(window->getSize().x/2, window->getSize().y/2+150), font);
    buttonPlay.insererTexte("Play");
    buttonPlay.SetFontColor(GameStyle::gameFontColor);
    buttonPlay.SetSize(window->getSize().x / 2, window->getSize().y / 15);

	exitButton.init(500, 15, Vector2f(window->getSize().x / 2, window->getSize().y / 2 + 215), font);
	exitButton.insererTexte("Exit Game");
	exitButton.SetFontColor(GameStyle::gameRedColor);
	exitButton.SetSize(window->getSize().x / 2, window->getSize().y / 15);

    this->mainWin = window;
    isRunning = true;

    return true;
}

void MainMenu::getInputs()
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

        //Si on a un événement de click de souris
        if (event.type == Event::MouseButtonPressed)
        {
            //Si on touche à la textbox avec la souris
            if (buttonPlay.touche(Mouse::getPosition(*mainWin)))
            {
                currentButton = &buttonPlay;
                currentButton->selectionner(GameStyle::gameButtonColor);
                currentButtonType = PLAY_BUTTON;
            }
			else if (exitButton.touche(Mouse::getPosition(*mainWin)))
			{
				currentButton = &exitButton;
				currentButton->selectionner(GameStyle::gameButtonColor);
				currentButtonType = EXIT;
			}
            else
            {
                //Sinon aucun textbox actif
                //Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
                currentButton = nullptr;
                buttonPlay.deSelectionner();
            }

        }
    }
}

void MainMenu::update()
{
    if (currentButtonType == PLAY_BUTTON)
    {
        transitionVersScene = Scene::GAME;
        isRunning = false;
    }
	else if (currentButtonType == EXIT)
	{
		transitionVersScene = Scene::EXIT;
		isRunning = false;
	}
}

void MainMenu::draw()
{
    mainWin->clear();
    mainWin->draw(ecranTitre);
    buttonPlay.dessiner(mainWin);
	exitButton.dessiner(mainWin);
    mainWin->display();
}

void spaceShooter::MainMenu::DeselectButtons()
{
    buttonPlay.deSelectionner();
    currentButtonType = NONE;
}
