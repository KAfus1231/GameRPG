#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"

class Player;

class Map
{
private:
	friend class Player;
	friend class Enemy;

	sf::Texture tileSheetTexture; // текстура карты
	sf::Sprite sprite;

	static const int mapHeight = 20; // высота карты в плитках
	static const int mapWidth = 35; // ширина

	sf::String firstLayer[mapHeight]; // строка элементов для отрисовки карты
	sf::String secondLayer[mapHeight];
	sf::String thirdLayer[mapHeight];

	std::vector<sf::Sprite> firstLayerObjects; // вектор для хранения плиток и инфы о них
	std::vector<sf::Sprite> secondLayerObjects;
	std::vector<sf::Sprite> thirdLayerObjects;

	std::vector<sf::RectangleShape> mapHitbox; // хитбоксы для обхектов на карте
	sf::RectangleShape hitbox;

	int tileWidth; // кол-во пикселей в плитке по ширине
	int tileHeight; // по высоте

	int totalTilesX; // плитки по X
	int totalTilesY; // плитки по Y

public: 
	Map();
	~Map();

	void LayerLoad(sf::String layer[], std::vector<sf::Sprite> &layerObjects);
	void CreateHitbox(sf::Sprite &sprite, int x, int y, int posX, int posY);
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void DrawFirstLayer(sf::RenderWindow& window);
	void DrawSecondLayer(sf::RenderWindow& window);
};

