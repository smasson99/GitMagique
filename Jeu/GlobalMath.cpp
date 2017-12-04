#include "GlobalMath.h"

Vector2f spaceShooter::GlobalMath::InspectPos(Vector2f pos, Vector2f point1, Vector2f point2)
{
    Vector2f res = pos;

    if (pos.x < point1.x)
    {
        res.x = point1.x;
    }
    else if (pos.x > point2.x)
    {
        res.x = point2.x;
    }

    if (pos.y < point1.y)
    {
        res.y = point1.y;
    }
    else if (pos.y > point2.y)
    {
        res.y = point2.y;
    }

    return res;
}

bool spaceShooter::GlobalMath::IsOutOfScreen(Vector2f  pos)
{
    return (pos.y < 0 || pos.y > Background::WinHeight() || pos.x < 0 || pos.x > Background::RightLimit());
}
