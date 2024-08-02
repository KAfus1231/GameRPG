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
	firstLayer[0] = "IIIIIIIIIIIIIIIIIIII";
	firstLayer[1] = "I000000000000000000I";
	firstLayer[2] = "I000000000000000000I";
	firstLayer[3] = "I000000000000000000I";
	firstLayer[4] = "I000000000000000000I";
	firstLayer[5] = "I0III00000000000000I";
	firstLayer[6] = "I000000000000000000I";
	firstLayer[7] = "I000000000IIII00000I";
	firstLayer[8] = "I000000000000000000I";
	firstLayer[9] = "IIIIIIIIIIIIIIIIIIII";

	secondLayer[0] = "IIIIIIIIIIIIIIIIIIII";
	secondLayer[1] = "I00S000000000000000I";
	secondLayer[2] = "I000000000000000000I";
	secondLayer[3] = "I00000000000000BB00I";
	secondLayer[4] = "I00S00000000000S000I";
	secondLayer[5] = "I0IIIS0000000000000I";
	secondLayer[6] = "I000000000000S00000I";
	secondLayer[7] = "I000000000IIII00000I";
	secondLayer[8] = "I0BB000000000000000I";
	secondLayer[9] = "IIIIIIIIIIIIIIIIIIII";

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

	LayerLoad(firstLayer, firstLayerObjects); // �������� �������� ������� ����
	LayerLoad(secondLayer, secondLayerObjects); // �������� �������� ������� ����

}

void Map::LayerLoad(sf::String layer[], std::vector<sf::Sprite>& layerObjects)
{
	for (int i = 0; i < mapHeight; i++) // ���������� �� ��������
		for (int j = 0; j < mapWidth; j++) // � ��� �� ������
		{
			switch (layer[i][j])
			{
			case('0'): // ���� 0 ����� ���
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 10, tileWidth, tileHeight)); // ��� ��� ���
				sprite.setScale(sf::Vector2f(5, 5)); // ����� ������ � 16 �� 16 * Scale.x(.y)
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite); // ����� ������ � ������ ��� ���� � ���
				break;
			case('I'): // ���� I ����� �����
				sprite.setTextureRect(sf::IntRect(tileWidth * 10, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				mapObjects.push_back(sprite); // ���� ����������� �����, �� ������ �� � ������ � ��������� �����
				break;
			case('S'): // �������
				sprite.setTextureRect(sf::IntRect(tileWidth * 15, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				break;
			case('B') : // �����
				sprite.setTextureRect(sf::IntRect(tileWidth * 8, tileHeight * 5, tileWidth, tileHeight  *2));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 4);
				mapObjects.push_back(sprite);
				layerObjects.push_back(sprite);
			}

		}
}

void Map::Update(float deltaTime) // �������������� ������ � �����
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (const auto & tiles : firstLayerObjects)
		window.draw(tiles);

	for (const auto& tiles : secondLayerObjects)
		window.draw(tiles);
}
