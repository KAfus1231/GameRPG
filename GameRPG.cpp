#include <SFML/Graphics.hpp>
#include "Constans.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
    // создание окна
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 16; // буферизация
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Default, settings);
    window.setFramerateLimit(144); // ограничение кадров
 
    Player player;
    Enemy enemy;

    enemy.Initialize();
    player.Initialize();

    player.Load();
    enemy.Load();
  
    while (window.isOpen())
    {
        sf::Event event; // событие
        while (window.pollEvent(event)) // обработка событий
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(); // очистка окна
        enemy.Update();
        player.Update(event, window);
        enemy.Draw(window);
        player.Draw(window);
        window.display(); // отрисовка
    }

    return 0;
 }
