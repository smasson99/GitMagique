#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Classe abstraite avec aucune méthode concrétisée.  Un .h suffit donc.
/// </summary>
namespace spaceShooter
{
    class Scene
    {
    public:
        //Les scènes disponibles
        enum scenes { MAIN_MENU, GAME, END_GAME, EXIT };

        virtual ~Scene() {}  //Pour que le destructeur de l'objet en mémoire soit apellé
        virtual scenes run() = 0;

        //La boucle de jeu est maintenant gérée par la scène
        virtual bool init(RenderWindow * const window) = 0;
        virtual void getInputs() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

    protected:
        RenderWindow *mainWin;
        Event event;

        /// <summary>
        /// À la fin de chaque scène, on indique à Game quelle nouvelle scène elle doit charger.
        /// </summary>
        Scene::scenes transitionVersScene;
        bool isRunning;
    };
}