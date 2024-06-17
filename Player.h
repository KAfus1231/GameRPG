#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

class Player
{
private:
	// �������� ������
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Clock clockForAnimation; // ������ ��� ��������
	float frame = 0; // ���� ���������
	float frameSpeed = 0.2f; //�������� ����� ������ ��������

	sf::Clock clockForBullets; // ������ ��� ����
	float bulletsSpeed = 0.08f; // �������� ����� ������ ��������
	float bulletSpeed = 10.0f; // �������� ����

	sf::Vector2f direction; // ����������� ����
	std::vector<sf::RectangleShape> bullets; // ������ � ������
	std::vector<sf::Vector2f> bulletsDirection; // ������, �������� ����������� ����
public:
	// ����� 
	sf::Sprite getPlayerSprite();
	void Initialize();
	void Load();
	void Update(sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	// ����
	sf::Vector2f BulletWatch(sf::RenderWindow& window);// ������ �� �������� 
};
