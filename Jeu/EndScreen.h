#pragma once
// <Sberube>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"


using namespace sf;

namespace spaceShooter
{
	class EndScreen : public Scene
	{
	public:
		EndScreen();
		~EndScreen();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:

		void DeselectButtons();

		Texture screenTexture;
		Sprite ecranTitre;
		Font font;

		Button replayButton;
		Button exitButton;
		Button ScoreLabel;

		//Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
		Button* currentButton = nullptr;

		enum ButtonType
		{
			NONE,
			REPLAY,
			EXIT
		};
		ButtonType currentButtonType = NONE;
	};
}
// </Sberube>