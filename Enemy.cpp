#include"Enemy.h"
#include<iostream>
#include"Constans.h"

Enemy::Enemy() : health(100)
{

}

Enemy::~Enemy()
{
}

sf::Sprite Enemy::getEnemySprite() // геттер для спрайта
{
    return sprite;
}

void Enemy::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent); // контур
    boundingRectangle.setOutlineColor(sf::Color::Red); // цвет контура
    boundingRectangle.setOutlineThickness(1); // толщина контура

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

        healthFont.loadFromFile("assets/fonts/Arial.ttf"); // загрузка шрифта для полоски hp
        healthText.setFont(healthFont); // установка шрифта для полоски hp

        sprites.push_back(sprite); // добавление спрайта в вектор
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update(Player& player, float deltaTime)
{
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds();
    
    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
    {
        clockForAnimation.restart();
    }


    if(health > 0)
    {
        sf::Vector2f direction = player.getPlayerSprite().getPosition() - sprites[spritesNumber].getPosition(); // направление для движения врага
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
        if (direction.x > 0)
        {
            frame += timeForAnimation;
            if (frame > 9)
                frame = 0;
            sprites[spritesNumber].setTextureRect(sf::IntRect(64 * int(frame), 196, 64, 64));
        }

        boundingRectangle.setPosition(sprites[spritesNumber].getPosition()); // рамка привязана к спрайту врага

        healthText.setString(std::to_string(health)); // установка полоски hp
        healthText.setPosition(sprites[spritesNumber].getPosition().x + // ->
            (128 - healthText.getGlobalBounds().width) / 2, sprites[spritesNumber].getPosition().y - healthText.getGlobalBounds().height); // установка позиции полоски hp

        if (sprites[spritesNumber].getGlobalBounds().intersects(player.getPlayerSprite().getGlobalBounds())) // обработка столкновений врага и игрока
        {
            player.boundingRectangle.setOutlineColor(sf::Color::Red);
        }

        else
            player.boundingRectangle.setOutlineColor(sf::Color::Blue);

        for (int i = 0; i < player.bullets.size(); i++) // обработка столкновений пуль и врага
        {
            if (sprites[spritesNumber].getGlobalBounds().intersects(player.bullets[i].getGlobalBounds()))
            {
                health -= 10;
                std::cout << "Enemy Health is: " << health << std::endl;
                boundingRectangle.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
                player.bullets.erase(player.bullets.begin() + i); // удаление пули при попадании во врага
                player.bulletsDirection.erase(player.bulletsDirection.begin() + i); // удаление направления пули при попадании во врага

            }
            else
            {
                boundingRectangle.setOutlineColor(sf::Color::Red);
            }
        }
    }
    else // если hp стало 0
    {
        health = 100;

        spritesNumber += 1;
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
        window.draw(healthText);
    }
}
