// <Sberube>
#include "EndScreen.h"
#include "GameStyle.h"

using namespace spaceShooter;

EndScreen::EndScreen()
{

}

EndScreen::~EndScreen()
{
	currentButton = nullptr;
	delete currentButton;
}

Scene::scenes EndScreen::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool EndScreen::init(RenderWindow * const window)
{

	if (!font.loadFromFile("Ressources\\Fonts\\STJEDISE.ttf"))
	{
		return false;
	}

	ecranTitre.setTexture(screenTexture);

	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'écran
	replayButton.init(500, 15, Vector2f(window->getSize().x / 2, window->getSize().y / 2 + 150), font);
	replayButton.insererTexte("Play Again");
	replayButton.SetFontColor(GameStyle::gameFontColor);
	replayButton.SetSize(window->getSize().x / 2, window->getSize().y / 15);

	exitButton.init(500, 15, Vector2f(window->getSize().x / 2, window->getSize().y / 2 + 215), font);
	exitButton.insererTexte("Exit Game");
	exitButton.SetFontColor(GameStyle::gameRedColor);
	exitButton.SetSize(window->getSize().x / 2, window->getSize().y / 15);

	ScoreLabel.initInfo(Vector2f(window->getSize().x / 2, window->getSize().y / 2 - 50), font, true);
	ScoreLabel.insererTexte("Score: ");
	ScoreLabel.SetFontColor(GameStyle::gameFontColor);
	ScoreLabel.SetSize(window->getSize().x / 2, window->getSize().y / 15);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void EndScreen::getInputs()
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
			if (replayButton.touche(Mouse::getPosition(*mainWin)))
			{
				currentButton = &replayButton;
				currentButton->selectionner(GameStyle::gameButtonColor);
				currentButtonType = REPLAY;
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
				replayButton.deSelectionner();
			}

		}
	}
}

void EndScreen::update()
{
	if (currentButtonType == REPLAY)
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

void EndScreen::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	replayButton.dessiner(mainWin);
	exitButton.dessiner(mainWin);
	ScoreLabel.dessiner(mainWin);
	mainWin->display();
}

void EndScreen::DeselectButtons()
{
	replayButton.deSelectionner();
	exitButton.deSelectionner();
	currentButtonType = NONE;
}
// </Sberube>