#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
private:
	// текстура врага
	sf::Texture texture;
	sf::Sprite sprite;
	float bulletSpeed = 2.5f; // скорость игрока
public:
	sf::Sprite getEnemySprite();
	void Initialize();
	void Load();
	void Update(Player& player);
	void Draw(sf::RenderWindow& window);
};

