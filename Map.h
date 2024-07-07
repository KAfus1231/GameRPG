#pragma once
#include <SFML/Graphics.hpp>

class Map
{
private:
	sf::Texture tileSheetTexture;
	sf::Sprite sprite;
	std::vector<sf::Sprite> tiles; // ������ ������

	int tileWidth; // ���-�� �������� � ������ �� ������
	int tileHeight; // �� ������

	int totalTilesX; // ������ �� X
	int totalTilesY; // ������ �� Y

public: 
	Map();
	~Map();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

