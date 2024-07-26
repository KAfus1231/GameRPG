#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Plaeyr;

class Info
{
private:
	sf::Text frameRateText; // עוךס הכÿ פנוילהאעû
	sf::Font font; // רנטפע
	int timeToFpsChange = 0;
public:
	Info();
	~Info();

	void Initialize();
	void Load();
	void Update(sf::Time deltaTimeTimer, Player &player);
	void Draw(sf::RenderWindow &window);
};

