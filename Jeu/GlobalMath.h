#pragma once
#include <SFML\Graphics.hpp>
#include "Background.h"

using namespace sf;


namespace spaceShooter
{
    class GlobalMath
    {
    public:
        static Vector2f InspectPos(Vector2f pos, Vector2f point1, Vector2f point2);
        static bool IsOutOfScreen(Vector2f pos);
    private:
    };
}