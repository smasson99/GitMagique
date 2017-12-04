#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace spaceShooter
{
    /// <summary>
    /// Nouvelle version de la classe game.  À présent elle sera surtout chargée de charger les différentes scènes
    /// testTest est toujours présent pour que vous puissez faire le lien avec les test unitaires
    /// </summary>
    class Game
    {
    public:
        Game();
        ~Game();
        int run();
        int testTest();

    private:
        const int LARGEUR = 1280;
        const int HAUTEUR = 720;

        bool init();

        RenderWindow mainWin;
        Event event;
    };
}