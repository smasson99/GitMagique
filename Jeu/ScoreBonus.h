#pragma once
#include "Bonus.h"

using namespace spaceShooter;

namespace spaceShooter
{
    class ScoreBonus :public Bonus
    {
    public:
        ScoreBonus(const float radius, const Color color, const float bonusMagnitude, const float bonusDuration, const Vector2f pos);
        ~ScoreBonus();
        static bool Init(const char path[]);
        void AdjustVisual();
    private:
        static Texture texture;
    };
}