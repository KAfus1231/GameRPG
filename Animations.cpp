#include "Animations.h"

void Combat::CreateAnimation()
{
	try
	{
		if (!texture.loadFromFile("Assets/World/Dungeon/combat.png"))
			throw "void Combat::CreateAnimation";

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite.setScale(2, 2);
	}
	catch (const char* errMsg)
	{
		std::cerr << "Problem in: " << errMsg << std::endl;
	}
}

sf::Sprite* Combat::UpdateAnimation()
{
	float timeForCombat = clockForAnimations.getElapsedTime().asSeconds();
	if (timeForCombat > frameSpeed)
	{
		frame++;
		if (frame > 7)
			frame = 0;

		sprite.setTextureRect(sf::IntRect(frame * 64, 0, 64, 64));
		clockForAnimations.restart();
	}
	return &sprite;
}

sf::Sprite* Combat::getSprite()
{
	return &sprite;
}
