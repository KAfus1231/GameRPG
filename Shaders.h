#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

class Shaders
{
private:
	sf::Shader shader;
public:
	virtual void CreateShader() = 0;
};
