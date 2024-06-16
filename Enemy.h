#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	// �������� �����
	sf::Texture texture;
	sf::Sprite sprite;
public:
	sf::Sprite getEnemySprite();
	void Initialize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
};

