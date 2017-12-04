#pragma once
// <sberube>
#include "Star.h"
#include "List.h"
#include <vector>
namespace spaceShooter
{ 
	class Background
	{
	public:

		Background();

		bool Init(RenderWindow &win);
		void Update(RenderWindow &win);
		void Draw(RenderWindow &win);
		void SetSpeed(float speed);
		static float RightLimit();
		static float LeftLimit();
        static float WinHeight();

	private:


		float bgSpeed = 1;

		Sprite background;
		Texture bgTexture;
		const std::string bgTexturePath = "Ressources\\Background\\Background.jpg";

		Sprite left;
		Texture leftTexture;
		const std::string leftTexturePath = "Ressources\\Background\\LeftHUD.png";

		Sprite right;
		Texture rightTexture;
		const std::string rightTexturePath = "Ressources\\Background\\RightHUD.png";

		// Pour l'instant on y va avec un tableau.
		//List<Star> stars;
		std::vector<Star> stars;
		const int nbStars = 200;
		float starSpeed = 2;

	};
}
// </sberube>