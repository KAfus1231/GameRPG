#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Map
{
private:
	sf::Texture tileSheetTexture; // текстура карты
	sf::Sprite sprite;

	static const int mapHeight = 15; // высота карты в плитках
	static const int mapWidth = 25; // ширина

	sf::String mapPlan[mapHeight]; // строка элементов для отрисовки карты
	std::vector<sf::Sprite> tiles; // вектор для хранения плиток и инфы о них

	int tileWidth; // кол-во пикселей в плитке по ширине
	int tileHeight; // по высоте

	int totalTilesX; // плитки по X
	int totalTilesY; // плитки по Y

public: 
	Map();
	~Map();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

