﻿#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

class Enemy;

class Player
{
private:
	// текстура игрока
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2i size; // размер персонажа

	sf::Clock clockForAnimation; // таймер для анимаций
	float frame = 0; // кадр персонажа
	float frameSpeed = 0.2f; //скорость смены кадров анимации
	float playerSpeed = 0.2f; // скорость кента

	sf::Clock clockForBullets; // таймер для пуль
	float bulletsSpeed = 0.08f; // скорость смены кадров стрельбы
	float bulletSpeed = 2.0f; // скорость пули

	sf::Vector2f direction; // направление пули
	std::vector<sf::Vector2f> bulletsDirection; // вектор, хранящий направление пуль


public:
	// игрок 
	sf::RectangleShape boundingRectangle; // рамка для игрока
	sf::Sprite getPlayerSprite(); // доступ к спрайту игрока
	sf::RectangleShape getBullet(); // доступ к пулям
	void Initialize();
	void Load();
	void Update(sf::Event& event, sf::RenderWindow& window, float deltaTime);
	void Draw(sf::RenderWindow& window);
	// пули
	std::vector<sf::RectangleShape> bullets; // вектор с пулями
	sf::Vector2f BulletWatch(sf::RenderWindow& window);// слежка за курсором 
};
