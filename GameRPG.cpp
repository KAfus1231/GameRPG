#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>

#include "Map.h"
#include "Constans.h"
#include "Player.h"
#include "Enemy.h"
#include "Info.h"
#include "Animations.h"

int main()
{
    // создание окна
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // буферизация
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Default, settings);
    window.setFramerateLimit(144);
    sf::RectangleShape backGround;
    backGround.setFillColor(sf::Color(128, 0, 128));
    backGround.setSize(sf::Vector2f(10000, 10000));
    backGround.setPosition(1400, 800);
    backGround.setOrigin(5000, 5000);

    sf::Clock clock; // таймер для контроля частоты обновлений и скорости
    sf::Clock clockForSpawn; // таймер для создания врагов

    Info info;
    Map map;
    Player player;
    std::vector<Enemy> enemies;

    for (size_t i = 0; i < 1; i++)
    {
        Enemy enemy;
        enemies.push_back(enemy);
    }

    info.Initialize();
    map.Initialize();
    player.Initialize();

    // Инициализация объектов
    info.Load();
    map.Load();
    player.Load();

    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].Load();
    }

    // интервал спавна врагов
    const float spawnInterval = 2.0f; // интервал спавна врагов в секундах
    clockForSpawn.restart(); // Запуск таймера спавна

    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart(); // время, прошедшее с последнего обновления кадра
        const float deltaTime = deltaTimeTimer.asMilliseconds(); // сохраняем значение

        sf::Event event; // событие
        while (window.pollEvent(event)) // обработка событий
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        static int enemyCount = 0; // предел обработки врагов

        if (clockForSpawn.getElapsedTime().asSeconds() >= spawnInterval && enemyCount < enemies.size())
        {
            clockForSpawn.restart();
            if (enemies[enemyCount].getEnemyIsDead()) // удаление врага, если он умер
                enemies.erase(enemies.begin() + enemyCount);
            enemyCount++; // если таймер сработал, то предел стал выше
        }

        window.clear(); // очистка окна

        info.Update(deltaTimeTimer, player);
        map.Update(deltaTime);
        player.Update(event, window, deltaTime, enemies, map);

        for (size_t i = 0; i < enemyCount; i++)
        {
            enemies[i].Update(player, deltaTime, map);
        }

        map.DrawFirstLayer(window);
        player.Draw(window);

        for (size_t i = 0; i < enemyCount; i++)
        {
            enemies[i].Draw(window);
        }

        map.DrawSecondLayer(window);


        info.Draw(window);

        window.display(); // отрисовка
    }

    return 0;
}

