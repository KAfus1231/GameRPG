#include "Info.h"
#include <iostream>

Info::Info()
{
}

Info::~Info()
{
}

void Info::Initialize()
{
}

void Info::Load()
{
    if (font.loadFromFile("assets/fonts/Arial.ttf")) // �������� ������ �� �����
    {
        std::cout << "font loaded" << std::endl;
        frameRateText.setFont(font);
    }
    else
        std::cout << "Problem in info.cpp";
}

void Info::Update(sf::Time deltaTimeTimer, Player& player)
{
    const int fps = static_cast<int>(1 / deltaTimeTimer.asSeconds());

    if (timeToFpsChange >= 1) // ������� ������� ������ ��� � ������������ �����
    {
        frameRateText.setString("   FPS: " + std::to_string(fps));
        timeToFpsChange = 0;
    }
    timeToFpsChange += deltaTimeTimer.asSeconds() * 130; // ��� ��� ����� 
 
    frameRateText.setPosition(player.getPlayerSprite().getPosition() - sf::Vector2f(960, 540));
}

void Info::Draw(sf::RenderWindow &window)
{
    window.draw(frameRateText);
}
