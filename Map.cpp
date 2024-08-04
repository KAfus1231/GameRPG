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
	// ������ ����!!
	firstLayer[0] = "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII";
	firstLayer[1] = "I000000000000000000000000000000000I";
	firstLayer[2] = "I000000000000000000000000000000000I";
	firstLayer[3] = "I0000000I0000000000000000I00000000I";
	firstLayer[4] = "I00000000I00000000000000I000000000I";
	firstLayer[5] = "I000000000000000000000000000000000I";
	firstLayer[6] = "I000000000000000000000000000000000I";
	firstLayer[7] = "I00000000I00000000000000I000000000I";
	firstLayer[8] = "I0000000I0000000000000000I00000000I";
	firstLayer[9] = "I000000I00000000000000000000000000I";
	firstLayer[10] = "I00000I000000000000000000000000000I";
	firstLayer[11] = "I0000000000000000000000II000000000I";
	firstLayer[12] = "I000000000000000000000000000000000I";
	firstLayer[13] = "I000000000000000000000000000000000I";
	firstLayer[14] = "I000000II0000000000000III000000000I";
	firstLayer[15] = "I000000000000000000000000000000000I";
	firstLayer[16] = "I000000000000000000000000000000000I";
	firstLayer[17] = "I000000I00000000000000III000000000I";
	firstLayer[18] = "I000000000000000000000000000000000I";
	firstLayer[19] = "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII";

	// ������ ����!!
	secondLayer[0] = "                                   ";
	secondLayer[1] = "                                   ";
	secondLayer[2] = "                                   ";
	secondLayer[3] = "                                   ";
	secondLayer[4] = "        S                          ";
	secondLayer[5] = "                                   ";
	secondLayer[6] = "                                   ";
	secondLayer[7] = "        S                S         ";
	secondLayer[8] = "                                   ";
	secondLayer[9] = "        S                          ";
	secondLayer[10] = "                                   ";
	secondLayer[11] = "                 S                 ";
	secondLayer[12] = "                                   ";
	secondLayer[13] = "       S                           ";
	secondLayer[14] = "                         S         ";
	secondLayer[15] = "                       S           ";
	secondLayer[16] = "                                   ";
	secondLayer[17] = "                         S         ";
	secondLayer[18] = "                                   ";
	secondLayer[19] = "                                   ";

	// ������ ����!!���������!!
	thirdLayer[0] = "                                   ";
	thirdLayer[1] = "                                   ";
	thirdLayer[2] = "                                   ";
	thirdLayer[3] = "                                   ";
	thirdLayer[4] = "          B            B           ";
	thirdLayer[5] = "                                   ";
	thirdLayer[6] = "                                   ";
	thirdLayer[7] = "                                   ";
	thirdLayer[8] = "         B                         ";
	thirdLayer[9] = "                                   ";
	thirdLayer[10] = "       B                           ";
	thirdLayer[11] = "                                   ";
	thirdLayer[12] = "                                   ";
	thirdLayer[13] = "                                   ";
	thirdLayer[14] = "                                   ";
	thirdLayer[15] = "                                   ";
	thirdLayer[16] = "                                   ";
	thirdLayer[17] = "            B                      ";
	thirdLayer[18] = "                                   ";
	thirdLayer[19] = "                                   ";

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
	LayerLoad(thirdLayer, thirdLayerObjects);

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
				//�������� �������� ��� �������
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);

				layerObjects.push_back(sprite);
				break;
			case('S'): // �������
				sprite.setTextureRect(sf::IntRect(tileWidth * 15, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				break;
			case('B') : // �����
				sprite.setTextureRect(sf::IntRect(tileWidth * 8, tileHeight * 5 + 6, tileWidth, tileHeight + 4));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				// �������� �������� ��� �������
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, (tileHeight - 6) * sprite.getScale().y, 0, 40);
				
				layerObjects.push_back(sprite);
			}

		}
}

// ����� �������� ���������
void Map::CreateHitbox(sf::Sprite &sprite, int x, int y, int posX, int posY)
{
	std::cout << "CreateHitbox Working!" << std::endl;
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2);
	hitbox.setSize(sf::Vector2f(x, y));
	hitbox.setPosition(sprite.getPosition().x + posX, sprite.getPosition().y + posY);
	mapHitbox.push_back(hitbox);
}

void Map::Update(float deltaTime) // �������������� ������ � �����
{
}

void Map::DrawFirstLayer(sf::RenderWindow& window)
{
	for (const auto & tiles : firstLayerObjects)
		window.draw(tiles);

	for (const auto& tiles : secondLayerObjects)
		window.draw(tiles);

	for (const auto& hitbox : mapHitbox)
		window.draw(hitbox);
}

void Map::DrawSecondLayer(sf::RenderWindow& window)
{
	for (const auto& hitbox : thirdLayerObjects)
		window.draw(hitbox);
}
