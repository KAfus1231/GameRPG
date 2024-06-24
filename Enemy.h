#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
private:
	// текстура врага
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2i size; // размер врага
	sf::RectangleShape boundingRectangle; // рамка для врага
	float bulletSpeed = 2.5f; // скорость игрока
public:
	sf::Sprite getEnemySprite();
	void Initialize();
	void Load();
	void Update(Player& player, float deltaTime);
	void Draw(sf::RenderWindow& window);
};

