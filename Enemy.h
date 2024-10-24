﻿#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

class Map;
class Player;

class Enemy
{
private:
	// текстура врага
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture textureForDeath;
	sf::Sprite spriteForDeath;

	// анимация смерти
	bool isDead = false; // флаг смерти)
	bool deathAnimationComplete = false; // флан анимации смерти
	float frameDeathSpeed = 120.0f; // скорость смены кадров анимации смерти
	int currentDeathFrame = 0; // кадр анимации смерти
	float deathAnimationTime = 0.0f; // время прошедшее с прошлого кадра
	sf::Vector2f deathPosition; // позиция отрисовки анимации

	float frame = 0; // кадр врага
	float frameSpeed = 0.2f; //скорость смены кадров анимации

	// текст над врагом
	sf::RectangleShape boundingRectangleForHP; // обводка для HP
	sf::RectangleShape rectangleForHP; // полоска hp

	sf::Vector2i size; // размер врага
	sf::RectangleShape hitbox; // рамка для врага

	float EnemySpeed = 0.5f; // скорость врага
	sf::Vector2f direction; // направление врага
	sf::Vector2f collisionDirection; // направления столкновения

	sf::Clock clockForAnimation; // таймер для анимаций
	
	int health; // здоровье
public:
	Enemy();
	~Enemy();

	// методы действий врага
	void movement(Player & player, float deltaTime); // метод движения врага
	void collisions(Player& player, Map& map, float deltaTime); // метод обработки столкновений
	void status(); // метод вывода информации над врагом
	void death(); // метод обработки смерти одного из врагов
	void discardEnemy(float deltaTime, float bounceForce); // отбрасывание врага при столкновении
	void enemyDeathAnimation(float deltaTime); // анимация смрети

	sf::Vector2f getEnemyDirection(); // геттер направления врага
	sf::Sprite getEnemySprite();
	sf::RectangleShape getEnemyHitbox();
	bool getEnemyIsDead();
	void Initialize();
	void Load();
	void Update(Player& player, float deltaTime, Map& map);
	void Draw(sf::RenderWindow& window);
};

