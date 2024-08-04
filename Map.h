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

	static const int mapHeight = 20; // ������ ����� � �������
	static const int mapWidth = 35; // ������

	sf::String firstLayer[mapHeight]; // ������ ��������� ��� ��������� �����
	sf::String secondLayer[mapHeight];
	sf::String thirdLayer[mapHeight];

	std::vector<sf::Sprite> firstLayerObjects; // ������ ��� �������� ������ � ���� � ���
	std::vector<sf::Sprite> secondLayerObjects;
	std::vector<sf::Sprite> thirdLayerObjects;

	std::vector<sf::RectangleShape> mapHitbox; // �������� ��� �������� �� �����
	sf::RectangleShape hitbox;

	int tileWidth; // ���-�� �������� � ������ �� ������
	int tileHeight; // �� ������

	int totalTilesX; // ������ �� X
	int totalTilesY; // ������ �� Y

public: 
	Map();
	~Map();

	void LayerLoad(sf::String layer[], std::vector<sf::Sprite> &layerObjects);
	void CreateHitbox(sf::Sprite &sprite, int x, int y, int posX, int posY);
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void DrawFirstLayer(sf::RenderWindow& window);
	void DrawSecondLayer(sf::RenderWindow& window);
};

