#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include<iostream>

class Animations
{
protected:
	sf::Clock clockForAnimations;
	int frame;
	float frameSpeed = 0.125;
public:
	virtual void CreateAnimation() = 0;
	virtual sf::Sprite* UpdateAnimation() = 0;
};


class Combat : public Animations
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape hitbox;
public:
	void CreateAnimation() override;
	sf::Sprite* UpdateAnimation() override;
	sf::Sprite* getSprite();
};