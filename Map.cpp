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

	LayerLoad(firstLayer, firstLayerObjects); // загрузка объектов певрого сло€
	LayerLoad(secondLayer, secondLayerObjects); // загрузка объектов второго сло€

}

void Map::LayerLoad(sf::String layer[], std::vector<sf::Sprite>& layerObjects)
{
	for (int i = 0; i < mapHeight; i++) // пробегаюсь по столбцам
		for (int j = 0; j < mapWidth; j++) // а тут по строке
		{
			switch (layer[i][j])
			{
			case('0'): // если 0 рисую пол
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 10, tileWidth, tileHeight)); // вот сам пол
				sprite.setScale(sf::Vector2f(5, 5)); // мен€ю размер с 16 на 16 * Scale.x(.y)
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite); // кидаю плитку в вектор дл€ инфы о ней
				break;
			case('I'): // если I рисую стену
				sprite.setTextureRect(sf::IntRect(tileWidth * 10, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				mapObjects.push_back(sprite); // если встречаетс€ стена, то кидаем ее в вектор с объектами карты
				break;
			case('S'): // черепок
				sprite.setTextureRect(sf::IntRect(tileWidth * 15, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				break;
			case('B') : // бочка
				sprite.setTextureRect(sf::IntRect(tileWidth * 8, tileHeight * 5, tileWidth, tileHeight  *2));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 4);
				mapObjects.push_back(sprite);
				layerObjects.push_back(sprite);
			}

		}
}

void Map::Update(float deltaTime) // взаимодействие игрока и карты
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (const auto & tiles : firstLayerObjects)
		window.draw(tiles);

	for (const auto& tiles : secondLayerObjects)
		window.draw(tiles);
}
