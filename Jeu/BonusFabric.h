#pragma once
#include "Bonus.h"
#include "ScoreBonus.h"

using namespace spaceShooter;

namespace spaceShooter
{
    class BonusFabric
    {
    public:
        static Bonus* GetBonus(Bonus::BonusType type);
    };
}