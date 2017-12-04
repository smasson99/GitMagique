#include "ScoreBonus.h"

using namespace spaceShooter;

Texture ScoreBonus::texture;

ScoreBonus::ScoreBonus(const float radius, const Color color, const float bonusMagnitude, const float bonusDuration, const Vector2f pos) :Bonus(radius, color, bonusMagnitude, bonusDuration, pos)
{

}

ScoreBonus::~ScoreBonus()
{
}

bool spaceShooter::ScoreBonus::Init(const char path[])
{
    if (!texture.loadFromFile(path))
        return false;
    return true;
}

void spaceShooter::ScoreBonus::AdjustVisual()
{
    sprite->setTexture(texture);
}

