#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>

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

    sf::Text frameRateText; // текс для фреймдаты
    sf::Font font; // шрифт
    int timeToFpsChange = 0;

    sf::Clock clock; // таймер для контроля частоты обновлений и скорости

    Player player;
    Enemy enemy;

    player.Initialize();
    enemy.Initialize();

    if (font.loadFromFile("assets/fonts/Arial.ttf")) // загрузка шрифта из файла
    {
        std::cout << "font loaded" << std::endl;
        frameRateText.setFont(font);
    }
    else
        window.close();

    player.Load();
    enemy.Load();

    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.getElapsedTime(); // время, прошедшее с последнего обновления кадра
        const float deltaTime = deltaTimeTimer.asMilliseconds(); // сохраняем значение 

        const int fps = static_cast<int>(1 / deltaTimeTimer.asSeconds());

        if(timeToFpsChange >= 1) // выводим частоту кадров раз в определенное время
        {
            frameRateText.setString("   FPS: " + std::to_string(fps));
            timeToFpsChange = 0;
        }
        timeToFpsChange += deltaTimeTimer.asSeconds() * 130; // вот это время 

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

        window.draw(frameRateText);
        window.display(); // отрисовка
    }

    return 0;
}
