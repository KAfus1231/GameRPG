#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Player;

class Map
{
private:
	friend class Player;
	friend class Enemy;

	sf::Texture tileSheetTexture; // �������� �����
	sf::Sprite sprite;

	static const int mapHeight = 15; // ������ ����� � �������
	static const int mapWidth = 25; // ������

	sf::String mapPlan[mapHeight]; // ������ ��������� ��� ��������� �����
	std::vector<sf::Sprite> tiles; // ������ ��� �������� ������ � ���� � ���
	std::vector<sf::Sprite> mapObjects; // ������ ��� �������� �������� �����

	int tileWidth; // ���-�� �������� � ������ �� ������
	int tileHeight; // �� ������

	int totalTilesX; // ������ �� X
	int totalTilesY; // ������ �� Y

public: 
	Map();
	~Map();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

