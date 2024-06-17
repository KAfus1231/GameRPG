#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

class Player
{
private:
	// текстура игрока
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Clock clockForAnimation; // таймер для анимаций
	float frame = 0; // кадр персонажа
	float frameSpeed = 0.2f; //скорость смены кадров анимации

	sf::Clock clockForBullets; // таймер для пуль
	float bulletsSpeed = 0.08f; // скорость смены кадров стрельбы
	float bulletSpeed = 10.0f; // скорость пули

	sf::Vector2f direction; // направление пули
	std::vector<sf::RectangleShape> bullets; // вектор с пулями
	std::vector<sf::Vector2f> bulletsDirection; // вектор, хранящий направление пуль
public:
	// игрок 
	sf::Sprite getPlayerSprite();
	void Initialize();
	void Load();
	void Update(sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	// пули
	sf::Vector2f BulletWatch(sf::RenderWindow& window);// слежка за курсором 
};
