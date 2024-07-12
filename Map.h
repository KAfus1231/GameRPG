#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Map
{
private:
	sf::Texture tileSheetTexture; // �������� �����
	sf::Sprite sprite;

	static const int mapHeight = 15; // ������ ����� � �������
	static const int mapWidth = 25; // ������

	sf::String mapPlan[mapHeight]; // ������ ��������� ��� ��������� �����
	std::vector<sf::Sprite> tiles; // ������ ��� �������� ������ � ���� � ���

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

