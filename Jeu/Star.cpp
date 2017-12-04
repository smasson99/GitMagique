// <sberube>
#include "Star.h"

using namespace spaceShooter;

Star::Star() : brtChance(2)
{
	shape.setRadius(2);
	shape.setFillColor(Color::White);
}

bool Star::Init()
{
	return true;
}

void Star::Update()
{
	// Le brillant des étoiles
	int random = rand() % 100;
	if (random < brtChance)
	{
		int rdn = rand() % 2;
		shape.setFillColor(colors[rdn]);
	}
}

void Star::Draw(RenderWindow &win)
{
	win.draw(shape);
}

void Star::SetPosition(float x, float y)
{
	shape.setPosition(x, y);
}

Vector2f Star::GetPosition()
{
	return shape.getPosition();
}
// </sberube>