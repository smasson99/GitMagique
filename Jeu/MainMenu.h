#pragma once
//class SceneTitre
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"


using namespace sf;

namespace spaceShooter
{
    class MainMenu : public Scene
    {
    public:
        MainMenu();
        ~MainMenu();

        scenes run();
        bool init(RenderWindow * const window);
        void getInputs();
        void update();
        void draw();

    private:

        void DeselectButtons();

        //L'écran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
        Texture ecranTitreT;
        Sprite ecranTitre;
        Font font;
        //Le bouton "play"
        Button buttonPlay;
		Button exitButton;

        //Ne fait pas beaucoup sens à un Textbox, mais à plusieurs, ça le fera.
        Button* currentButton = nullptr;

        enum ButtonType
        {
            NONE,
            PLAY_BUTTON,
			EXIT
        };
        ButtonType currentButtonType = NONE;
    };
}
