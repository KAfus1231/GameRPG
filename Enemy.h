#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
private:
	// текстура врага
	std::vector<sf::Sprite> sprites; // вектор спрайтов врага
	sf::Texture texture;
	sf::Sprite sprite;
	int spritesNumber = 0; // номер текущего спрайта в векторе

	// текст над врагом
	sf::Text healthText;
	sf::Font healthFont;

	sf::Vector2i size; // размер врага
	sf::RectangleShape boundingRectangle; // рамка для врага

	sf::Clock clockForAnimation; // таймер для анимаций
	float frame = 0; // кадр врага
	float frameSpeed = 0.2f; //скорость смены кадров анимации
	float EnemySpeed = 0.6f; // скорость врага
	
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

