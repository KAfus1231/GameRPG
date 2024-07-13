#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0)
{
}

Map::~Map()
{
}

void Map::Initialize() // карта 
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
	totalTilesX = tileSheetTexture.getSize().x / tileWidth; // получаем количество плиток по x
	totalTilesY = tileSheetTexture.getSize().y / tileHeight; // по y

	std::cout << totalTilesX << " " << totalTilesY << std::endl;

	try // пытаюсь загрузить текстуру
	{
		tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png");
		sprite.setTexture(tileSheetTexture); // установка спрайта
		std::cout << "Tileset load!" << std::endl;

		if(!tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png"))
			throw "void::Map::Load()"; // выкидываю ошибку
	}
	catch (const char* errMsg)
	{
		std::cerr << "Problem:" << errMsg << std::endl; // ловлю ошибку
	}

	for(int i = 0; i < mapHeight; i++) // пробегаюсь по столбцам
		for(int j = 0; j < mapWidth; j++) // а тут по строке
			switch(mapPlan[i][j]) 
			{
			case('0') : // если 0 рисую пол
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 10, tileWidth, tileHeight)); // вот сам пол
				sprite.setScale(sf::Vector2f(5, 5)); // мен€ю размер с 16 на 16 * Scale.x(.y)
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				tiles.push_back(sprite); // кидаю плитку в вектор дл€ инфы о ней
				break;
			case('I') : // если I рисую стену
				sprite.setTextureRect(sf::IntRect(tileWidth * 10, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				tiles.push_back(sprite);
				break;
			}
}

void Map::Update(float deltaTime) // взаимодействие игрока и карты
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < mapHeight * mapWidth; i++)
		window.draw(tiles[i]);
}
