#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Map.h"
#include <cmath>

class Map;
class Enemy;

class Player
{
private:
	// параметры кента
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i size; // размер кента
	sf::Vector2f playerDirection; // направление игрока
	sf::RectangleShape hitbox; // хитбокс

	// флаги для движения персонажа
	bool isMovingUp;
	bool isMovingLeft;
	bool isMovingDown;
	bool isMovingRight;
	bool reloadDash = false; // флаг для перезарядки дэша
	bool isDash; // флаг для дэша
	sf::Vector2f previousPosition;

	float playerSpeed = 0.2f; // скорость кента
	int health; // здоровье кента
	int dashEnergy; // энегрия для дэша

	// текст над игроком
	sf::RectangleShape boundingRectangleForHP; // обводка для HP
	sf::RectangleShape rectangleForHP; // полоска hp
	sf::RectangleShape rectangleForDash; // полоска дэша

	sf::Clock clockForAnimation; // таймер для анимаций
	sf::Clock clockForCollision; // таймер для обработки событий при столкновении игрока и врага
	sf::Clock clockForBullets; // таймер для пуль
	sf::Clock clockForDash; // таймер для рывка
	sf::Clock clockForSpeed; // таймер для измерения скорости

	float frame = 0; // кадр персонажа
	float frameSpeed = 0.2f; //скорость смены кадров анимации

	float bulletsSpeed = 0.08f; // скорость смены кадров стрельбы
	float bulletSpeed = 1.5f; // скорость пули

	sf::View view; // камера для наблюдения за игроком
public:
	// игрок 
	Player();
	~Player();
	sf::Sprite getPlayerSprite(); // доступ к спрайту игрока
	sf::RectangleShape getBullet(); // доступ к пулям
	sf::RectangleShape getHitbox(); // доступ к хитбоксу

	// методы действий игрока
	void shoot(sf::RenderWindow& window, float deltaTime); // метод стрельбы
	void movement(sf::Event& event, float deltaTime); // метод передвижения
	void collisions(Enemy& enemy, Map & map, float deltaTime); // метод обработки столкновений
	void status(); // метод вывода и изменения информации над игроком
	sf::Vector2f getPlayerSpeed(float deltaTime);
	sf::View camera(sf::View view); // метод камеры

	void Initialize();
	void Load();
	void Update(sf::Event& event, sf::RenderWindow& window, float deltaTime, Enemy &enemy, Map & map);
	void Draw(sf::RenderWindow& window);
	// пули
	sf::Vector2f bulletDirection; // направление пули
	std::vector<sf::Vector2f> bulletsDirection; // вектор, хранящий направление пуль
	std::vector<sf::RectangleShape> bullets; // вектор с пулями
};
