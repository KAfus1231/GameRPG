#include <SFML/Graphics.hpp>
#include "Constans.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
    // �������� ����
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // �����������
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Default, settings);
    window.setFramerateLimit(144); // ����������� ������

    Player player;
    Enemy enemy;

    player.Initialize();
    enemy.Initialize();

    player.Load();
    enemy.Load();

    while (window.isOpen())
    {
        sf::Event event; // �������
        while (window.pollEvent(event)) // ��������� �������
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(); // ������� ����
        player.Update(event, window);
        enemy.Update(player);
        player.Draw(window);
        enemy.Draw(window);
        window.display(); // ���������
    }

    return 0;
}

