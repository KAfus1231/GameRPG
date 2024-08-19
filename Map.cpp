#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(96), tileHeight(96), totalTilesX(0), totalTilesY(0)
{
}

Map::~Map() {}

void Map::Initialize() // ����� 
{
	// ������ ����!!
	firstLayer[0] =  "    0  0   0  0   0   0            ";
	firstLayer[1] =  "     0      0    0 0 0             ";
	firstLayer[2] =  "   0  0    0    0   0              ";
	firstLayer[3] =  "                                   ";
	firstLayer[4] =  "   0000000000000                   ";
	firstLayer[5] =  "   0000000000000                   ";
	firstLayer[6] =  "   0000000000000000000             ";
	firstLayer[7] =  "   0000000000000000000000000000    ";
	firstLayer[8] =  " 000000000000000000000000000000    ";
	firstLayer[9] =  " 000000000000000000000000000000    ";
	firstLayer[10] = " 000000000000000000000000000000    ";
	firstLayer[11] = " 000000000000000000000000000000    ";
	firstLayer[12] = " 000000000000000000000000000000    ";
	firstLayer[13] = " 000000000000000000000000000000    ";
	firstLayer[14] = " 000000000000000000000000000000    ";
	firstLayer[15] = "           00000000000000000000    ";
	firstLayer[16] = "           00000000000000000000    ";
	firstLayer[17] = "                                   ";
	firstLayer[18] = "                                   ";
	firstLayer[19] = "                                   ";

	// ������ ����!!
	secondLayer[0] =  "                                   "; 
	secondLayer[1] =  "                                   "; 
	secondLayer[2] =  "                                   "; 
	secondLayer[3] =  "                                   "; 
	secondLayer[4] =  "   [-----------]                   "; 
	secondLayer[5] =  "   1           2                   "; 
	secondLayer[6] =  "   1           <-----]             "; 
	secondLayer[7] =  "   1                 <--------]    "; 
	secondLayer[8] =  " (->                          2    "; 
	secondLayer[9] =  "                              2    "; 
	secondLayer[10] = "                              2    "; 
	secondLayer[11] = " [-)       [-)                2    "; 
	secondLayer[12] = " 1         1                  2    "; 
	secondLayer[13] = " 1         1                  2    "; 
	secondLayer[14] = " {---------1                  2    "; 
	secondLayer[15] = "           1                  2    "; 
	secondLayer[16] = "           {------------------}    "; 
	secondLayer[17] = "                                   "; 
	secondLayer[18] = "                                   "; 
	secondLayer[19] = "                                   "; 

	// ������ ����!!���������!!
	thirdLayer[0] =  "                                   ";
	thirdLayer[1] =  "                                   ";
	thirdLayer[2] =  "                                   ";
	thirdLayer[3] =  "                                   ";
	thirdLayer[4] =  "   IIIIIIIIIIIII                   ";
	thirdLayer[5] =  "   I           I                   ";
	thirdLayer[6] =  "   I           IIIIIII             ";
	thirdLayer[7] =  "   I                 IIIIIIIIII    ";
	thirdLayer[8] =  " III                          I    ";
	thirdLayer[9] =  "                              I    ";
	thirdLayer[10] = "                              I    ";
	thirdLayer[11] = " III       III                I    ";
	thirdLayer[12] = " I         I                  I    ";
	thirdLayer[13] = " I         I                  I    ";
	thirdLayer[14] = " IIIIIIIIIII                  I    ";
	thirdLayer[15] = "           I                  I    ";
	thirdLayer[16] = "           IIIIIIIIIIIIIIIIIIII    ";
	thirdLayer[17] = "                                   ";
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
		tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset x3.png");
		sprite.setTexture(tileSheetTexture); // ��������� �������
		std::cout << "Tileset load!" << std::endl;

		if(!tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset x3.png"))
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
			case('0'): // ���
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 34 , tileHeight * 1, tileWidth, tileHeight)); // ��� ��� ���
				sprite.setPosition(j * tileWidth, i * tileHeight);
				layerObjects.push_back(sprite); // ����� ������ � ������ ��� ���� � ���
				break;
			case('-'): // �������������� �����
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 5, tileHeight * 0, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				//�������� �������� ��� �������
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('('): // ��������� ����� �����
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 12, tileHeight * 1, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				//�������� �������� ��� �������
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case(')'): // ��������� ����� ������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 14, tileHeight * 5, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				//�������� �������� ��� �������
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('1'): // ������������ ����� �����
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 2, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, 21, tileHeight, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('2'): // ������������ ����� ������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 9, tileHeight * 2, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, 21, tileHeight, 75, 0);
				layerObjects.push_back(sprite);
				break;
			case(']'): // �������� ����� �� ������� ������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 8, tileHeight * 0, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				CreateHitbox(sprite, 21, tileHeight, 75, 0);
				layerObjects.push_back(sprite);
				break;
			case('['): // �������� ����� ������ ������� ������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 0, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				CreateHitbox(sprite, 21, tileHeight, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('{'): // �������� ����� ������ ������� �����
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 4, tileHeight * 2, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('<'): // ������� �� �������� ����� ������ �������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 8, tileHeight * 1, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, 21, 48, 75, 0);
				layerObjects.push_back(sprite);
				break;
			case('}'): // �������� ����� �� ������� �����
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 6, tileHeight * 2, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, tileWidth, tileHeight / 2, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('>'): // ������� �� �������� ����� �� �������
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 1, tileWidth, tileHeight));
				sprite.setPosition(j * tileWidth, i * tileHeight);
				CreateHitbox(sprite, 21, 48, 0, 0);
				layerObjects.push_back(sprite);
				break;
			
			case('C'): // ������
				Combat* combat = new Combat();
				combat->CreateAnimation();
				combat->getSprite()->setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(*combat->getSprite(), tileWidth * 2, tileHeight * 6, 47, 25);
				animationObjects.push_back(combat);
				break;
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

// ��������� ������� ���� �����
void Map::DrawFirstLayer(sf::RenderWindow& window)
{
	for (const auto & tiles : firstLayerObjects)
		window.draw(tiles);

	for (const auto& tiles : secondLayerObjects)
		window.draw(tiles);

	for (size_t i = 0; i < animationObjects.size(); i++)
	{
		sf::Sprite* animSprite = animationObjects[i]->UpdateAnimation();
		window.draw(*animSprite);
	}

	/*for (const auto& hitbox : mapHitbox)
		window.draw(hitbox);*/
}

// ��������� ������� ���� �����
void Map::DrawSecondLayer(sf::RenderWindow& window)
{
	for (const auto& hitbox : thirdLayerObjects)
		window.draw(hitbox);
}
