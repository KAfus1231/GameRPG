#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
private:
	// текстура врага
	sf::Texture texture;
	sf::Sprite sprite;

	// текст над врагом
	sf::Text healthText;
	sf::Font healthFont;

	sf::Vector2i size; // размер врага
	sf::RectangleShape boundingRectangle; // рамка для врага
	float EnemySpeed = 0.4f; // скорость врага
	int health; // здоровье
public:
	Enemy();
	~Enemy();

	sf::Sprite getEnemySprite();
	void Initialize();
	void Load();
	void Update(Player& player, float deltaTime);
	void Draw(sf::RenderWindow& window);
};

