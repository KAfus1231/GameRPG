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

	static const int mapHeight = 10; // ������ ����� � �������
	static const int mapWidth = 20; // ������

	sf::String firstLayer[mapHeight]; // ������ ��������� ��� ��������� �����
	sf::String secondLayer[mapHeight];
	std::vector<sf::Sprite> firstLayerObjects; // ������ ��� �������� ������ � ���� � ���
	std::vector<sf::Sprite> mapObjects; // ������ ��� �������� �������� �����
	std::vector<sf::Sprite> secondLayerObjects;

	int tileWidth; // ���-�� �������� � ������ �� ������
	int tileHeight; // �� ������

	int totalTilesX; // ������ �� X
	int totalTilesY; // ������ �� Y

public: 
	Map();
	~Map();

	void LayerLoad(sf::String layer[], std::vector<sf::Sprite> &layerObjects);
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

