#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0)
{
}

Map::~Map()
{
}

void Map::Initialize() // ����� 
{
	mapPlan[0] =  "IIIIIIIIIIIIIIIIIIIIIIIII";
	mapPlan[1] =  "I00000000000000000000000I";
	mapPlan[2] =  "I00000000000000000000000I";
	mapPlan[3] =  "I00000000000000I00000000I";
	mapPlan[4] =  "I00000000000000000000000I";
	mapPlan[5] =  "I00000000000000000000000I";
	mapPlan[6] =  "I00000000000000000000000I";
	mapPlan[7] =  "I00000000000000000000000I";
	mapPlan[8] =  "I00000000000000000000000I";
	mapPlan[9] =  "I00000000000000000000000I";
	mapPlan[10] = "I00000000000000000000000I";
	mapPlan[11] = "I00000000000000000000000I";
	mapPlan[12] = "I00000000000000000000000I";
	mapPlan[13] = "I00000000000000000000000I";
	mapPlan[14] = "IIIIIIIIIIIIIIIIIIIIIIIII";
}

void Map::Load()
{
	totalTilesX = tileSheetTexture.getSize().x / tileWidth; // �������� ���������� ������ �� x
	totalTilesY = tileSheetTexture.getSize().y / tileHeight; // �� y

	std::cout << totalTilesX << " " << totalTilesY << std::endl;

	try // ������� ��������� ��������
	{
		tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png");
		sprite.setTexture(tileSheetTexture); // ��������� �������
		std::cout << "Tileset load!" << std::endl;

		if(!tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png"))
			throw "void::Map::Load()"; // ��������� ������
	}
	catch (const char* errMsg)
	{
		std::cerr << "Problem:" << errMsg << std::endl; // ����� ������
	}

	for(int i = 0; i < mapHeight; i++) // ���������� �� ��������
		for(int j = 0; j < mapWidth; j++) // � ��� �� ������
			switch(mapPlan[i][j]) 
			{
			case('0') : // ���� 0 ����� ���
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 10, tileWidth, tileHeight)); // ��� ��� ���
				sprite.setScale(sf::Vector2f(5, 5)); // ����� ������ � 16 �� 16 * Scale.x(.y)
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				tiles.push_back(sprite); // ����� ������ � ������ ��� ���� � ���
				break;
			case('I') : // ���� I ����� �����
				sprite.setTextureRect(sf::IntRect(tileWidth * 10, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				tiles.push_back(sprite);
				break;
			}
}

void Map::Update(float deltaTime) // �������������� ������ � �����
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < mapHeight * mapWidth; i++)
		window.draw(tiles[i]);
}
