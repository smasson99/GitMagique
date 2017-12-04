#include "BonusFabric.h"

Bonus * spaceShooter::BonusFabric::GetBonus(Bonus::BonusType type)
{
    Bonus* res = nullptr;

    switch (type)
    {
    case Bonus::BonusType::ScoreBonus_Type:
        res = new ScoreBonus(0.35f, Color::White, 2.0f, 10.0f, Vector2f(0, 0));
        //Conversion temporaire
        ScoreBonus* temp = (ScoreBonus*)res;
        temp->AdjustVisual();
        //Clean-up
        temp = nullptr;
        break;
    }

    return res;
}
