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
	totalTilesX = tileSheetTexture.getSize().x / tileWidth; // получаем количество плиток по x
	totalTilesY = tileSheetTexture.getSize().y / tileHeight; // по y

	std::cout << totalTilesX << " " << totalTilesY << std::endl;
	std::cout << "Tileset load!" << std::endl;

	if (tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png"))
	{
		tiles.push_back(sprite);
		tiles.front().setTexture(tileSheetTexture);
		tiles.front().setTextureRect(sf::IntRect(tileWidth,tileHeight, tileWidth, tileHeight));
		tiles.front().setScale(sf::Vector2f(5, 5));
		tiles.front().setPosition(sf::Vector2f(tileWidth * 5, 0));
	}
	
	else
		std::cout << "Not Loaded!" << std::endl;
}

void Map::Update(float deltaTime)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	window.draw(tiles.front());
}
