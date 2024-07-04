#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0)
{
}

Map::~Map()
{
}

void Map::Initialize()
{
}

void Map::Load()
{
	if (tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png"))
	{
		totalTilesX = tileSheetTexture.getSize().x / tileWidth; // получаем количество плиток по x
		totalTilesY = tileSheetTexture.getSize().y / tileHeight; // по y

		std::cout << totalTilesX << " " << totalTilesY << std::endl;
		std::cout << "Tileset load!" << std::endl;

		sprite.setTexture(tileSheetTexture);
		sprite.setTextureRect(sf::IntRect(2 * tileWidth, 4 * tileHeight, tileWidth, tileHeight));
		sprite.setScale(sf::Vector2f(5, 5));
		sprite.setPosition(sf::Vector2f(100, 100));
	}
	
	else
		std::cout << "Not Loaded!" << std::endl;
}

void Map::Update(float deltaTime)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
