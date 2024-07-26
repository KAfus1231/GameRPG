#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>

#include "Map.h"
#include "Constans.h"
#include "Player.h"
#include "Enemy.h"
#include "Info.h"


int main()
{
    // создание окна
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // буферизация
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Default, settings);
    window.setFramerateLimit(144);

    sf::Clock clock; // таймер для контроля частоты обновлений и скорости

    Info info;
    Map map;
    Player player;
    Enemy enemy;

    info.Initialize();
    map.Initialize();
    player.Initialize();
    enemy.Initialize();

    
    info.Load();
    map.Load();
    player.Load();
    enemy.Load();

    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.getElapsedTime(); // время, прошедшее с последнего обновления кадра
        const float deltaTime = deltaTimeTimer.asMilliseconds(); // сохраняем значение 
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
        info.Update(deltaTimeTimer, player);
        map.Update(deltaTime);
        player.Update(event, window, deltaTime, enemy, map);
        enemy.Update(player, deltaTime, map);

        map.Draw(window);
        player.Draw(window);
        enemy.Draw(window);
        info.Draw(window);

        window.display(); // отрисовка
    }

    return 0;
}
