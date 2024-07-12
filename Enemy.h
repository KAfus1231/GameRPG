#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Player;

class Enemy
{
private:
	// текстура врага
	std::vector<sf::Sprite> sprites; // вектор спрайтов врага
	sf::Texture texture;
	sf::Sprite sprite;
	int spritesNumber = 0; // номер текущего спрайта в векторе

	// текст над врагом
	sf::RectangleShape boundingRectangleForHP; // обводка для HP
	sf::RectangleShape rectangleForHP; // полоска hp

	sf::Vector2i size; // размер врага
	sf::RectangleShape boundingRectangle; // рамка для врага

	sf::Clock clockForAnimation; // таймер для анимаций
	float frame = 0; // кадр врага
	float frameSpeed = 0.2f; //скорость смены кадров анимации
	float EnemySpeed = 0.7f; // скорость врага
	sf::Vector2f direction; // направление врага

	int health; // здоровье
public:
	Enemy();
	~Enemy();

	sf::Vector2f getEnemyDirection();
	sf::Sprite getEnemySprite();
	void Initialize();
	void Load();
	void Update(Player& player, float deltaTime);
	void Draw(sf::RenderWindow& window);
};

