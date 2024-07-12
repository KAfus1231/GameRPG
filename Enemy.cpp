#include"Enemy.h"
#include<iostream>
#include"Constans.h"

Enemy::Enemy() : health(100)
{

}

Enemy::~Enemy()
{
}

sf::Vector2f Enemy::getEnemyDirection()
{
    return direction;
}

sf::Sprite Enemy::getEnemySprite() // геттер для спрайта
{
    return sprites[spritesNumber];
}

void Enemy::Initialize() {
    // хитбокс
    boundingRectangle.setFillColor(sf::Color::Transparent); // контур
    boundingRectangle.setOutlineColor(sf::Color::Red); // цвет контура
    boundingRectangle.setOutlineThickness(1); // толщина контура

    // рамка для hp
    boundingRectangleForHP.setFillColor(sf::Color::Transparent);
    boundingRectangleForHP.setOutlineColor(sf::Color::White);
    boundingRectangleForHP.setOutlineThickness(1);
    boundingRectangleForHP.setSize(sf::Vector2f(76, 10));

    // полоска hp
    rectangleForHP.setFillColor(sf::Color::Red);
    rectangleForHP.setSize(sf::Vector2f(76, 10));

    size = sf::Vector2i(64, 64); // размер врага
}

void Enemy::Load()
{
    if (texture.loadFromFile("Assets/Enemy/Textures/spritesheetEnemy.png")) // загрузка текстурки
    {
        std::cout << "enemy loaded" << std::endl;
        sprite.setTexture(texture);// врага

        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры врага
        sprite.setPosition(sf::Vector2f(400, 700)); // позиция врага

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер скелета
        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y)); // утсановка размера контура

        sprites.push_back(sprite); // добавление спрайта в вектор
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update(Player& player, float deltaTime)
{
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // таймер для смены анимаций
    
    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
    {
        clockForAnimation.restart();
    }

    if(health > 0)
    {
        direction = player.getPlayerSprite().getPosition() - sprites[spritesNumber].getPosition(); // направление для движения врага
        direction = Math::NormalizeVector(direction); // нормализация
        /*sprites[spritesNumber].setPosition(sprites[spritesNumber].getPosition() + direction * deltaTime * EnemySpeed);*/ // устоновка поцизии врага (бегает за игроком)
        
        if(direction.y < 0)
        {
            frame += timeForAnimation;
            if (frame > 9)
                frame = 0;
            sprites[spritesNumber].setTextureRect(sf::IntRect(64 * int(frame), 0, 64, 64));
        }
        if (direction.y > 0)
        {
            frame += timeForAnimation;
            if (frame > 9)
                frame = 0;
            sprites[spritesNumber].setTextureRect(sf::IntRect(64 * int(frame), 128, 64, 64));
        }
        if (direction.x < 0)
        {
            frame += timeForAnimation;
            if (frame > 9)
                frame = 0;
            sprites[spritesNumber].setTextureRect(sf::IntRect(64 * int(frame), 64, 64, 64));
        }
        if(direction.x > 0)
        {
            frame += timeForAnimation;
            if (frame > 9)
                frame = 0;
            sprites[spritesNumber].setTextureRect(sf::IntRect(64 * int(frame), 196, 64, 64));
        }

        for (int i = 0; i < player.bullets.size(); i++) // обработка столкновений пуль и врага
        {
            if (sprites[spritesNumber].getGlobalBounds().intersects(player.bullets[i].getGlobalBounds()))
            {
                health -= 10;
                boundingRectangle.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
                player.bullets.erase(player.bullets.begin() + i); // удаление пули при попадании во врага
                player.bulletsDirection.erase(player.bulletsDirection.begin() + i); // удаление направления пули при попадании во врага
                rectangleForHP.setSize(rectangleForHP.getSize() - sf::Vector2f(7.6, 0)); // уменьшение полоски hp при попадании 
            }
            else
                boundingRectangle.setOutlineColor(sf::Color::Red);
        }

        boundingRectangle.setPosition(sprites[spritesNumber].getPosition()); // рамка привязана к спрайту врага

        // позиция рамки для hp
        boundingRectangleForHP.setPosition(sprites[spritesNumber].getPosition().x + // ->
            (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprites[spritesNumber].getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
        // позиция полоски hp
        rectangleForHP.setPosition(sprites[spritesNumber].getPosition().x + // ->
            (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprites[spritesNumber].getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    }
    else // если hp стало 0
    {
        health = 100; // hp снова 100
        rectangleForHP.setSize(sf::Vector2f(76, 10)); // размер полоски hp снова полный
        spritesNumber += 1; // переход к следующему спрайту
        sprites.push_back(sprite);

        if (std::rand() % 2 == 1) // случайный спавн врага
            sprites[spritesNumber].setPosition(sf::Vector2f(std::rand() % 300, std::rand() % 1080));
        else
            sprites[spritesNumber].setPosition(sf::Vector2f(1920 - std::rand() % 300, rand() % 1080)); 
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.draw(sprites[spritesNumber]);
        window.draw(boundingRectangle);
        window.draw(rectangleForHP);
        window.draw(boundingRectangleForHP);
    }
}
