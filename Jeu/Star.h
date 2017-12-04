#pragma once
// <sberube>
#include <SFML\Graphics.hpp>

using namespace sf;

namespace spaceShooter
{	
	/// <summary>
	/// Une des deux couches du background.
	/// Classe pour les petites étoiles qui bougent.
	/// </summary>
	class Star
	{
	public:
		//Star(Texture texture);
		Star();

		bool Init();
		void Update();
		void Draw(RenderWindow &win);

		void SetPosition(float x, float y);
		Vector2f GetPosition();

	private:
		CircleShape shape;

		int brtChance; // pourcentage
		const Color colors[3]{Color::White, Color(225,225,225,0.9), Color(225,225,225,0.8)};
	};
}
// </sberube>