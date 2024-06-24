#include <SFML/Graphics.hpp>
#include<iostream>

#include "Constans.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
    // создание окна
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // буферизация
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Default, settings);
    window.setFramerateLimit(144);

    sf::Clock clock; // таймер для контроля частоты обновлений и скорости

    Player player;
    Enemy enemy;

    player.Initialize();
    enemy.Initialize();

    player.Load();
    enemy.Load();

    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.getElapsedTime(); // время, прошедшее с последнего обновления кадра
        const float deltaTime = deltaTimeTimer.asMilliseconds(); // сохраняем значение 
        std::cout << "   " << deltaTime << std::endl; // вывод на экран времени
        clock.restart();

        sf::Event event; // событие
        while (window.pollEvent(event)) // обработка событий
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(); // очистка окна
        player.Update(event, window, deltaTime);
        enemy.Update(player, deltaTime);
        player.Draw(window);
        enemy.Draw(window);
        window.display(); // отрисовка
    }

    return 0;
}
