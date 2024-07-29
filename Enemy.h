#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

class Map;
class Player;

class Enemy
{
private:
	// текстура врага
	std::vector<sf::Sprite> sprites; // вектор спрайтов врага
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture textureForDeath;
	sf::Sprite spriteForDeath;

	bool isDead = false;
	float frameDeathSpeed = 120.0f;
	int currentDeathFrame = 0;
	float deathAnimationTime = 0.0f;

	sf::Vector2f deathPosition;


	float frame = 0; // кадр врага
	float frameSpeed = 0.2f; //скорость смены кадров анимации
	int spritesNumber = 0; // номер текущего спрайта в векторе

	// текст над врагом
	sf::RectangleShape boundingRectangleForHP; // обводка для HP
	sf::RectangleShape rectangleForHP; // полоска hp

	sf::Vector2i size; // размер врага
	sf::RectangleShape hitbox; // рамка для врага

	float EnemySpeed = 0.7f; // скорость врага
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
	void enemyDeathAnimation(float deltaTime);

	sf::Vector2f getEnemyDirection();
	sf::Sprite getEnemySprite();
	sf::RectangleShape getEnemyHitbox();
	void Initialize();
	void Load();
	void Update(Player& player, float deltaTime, Map& map);
	void Draw(sf::RenderWindow& window);
};

