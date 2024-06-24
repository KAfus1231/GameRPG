#include"Enemy.h"
#include<iostream>
#include"Constans.h"

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
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update(Player& player, float deltaTime)
{
    sf::Vector2f direction = player.getPlayerSprite().getPosition() - sprite.getPosition(); // направление для движения врага
    direction = Math::NormalizeVector(direction); // нормализация
    //sprite.setPosition(sprite.getPosition() + direction * bulletSpeed); // устоновка поцизии врага (бегает за игроком)

    boundingRectangle.setPosition(sprite.getPosition()); // рамка привязана к спрайту врага

    if (sprite.getGlobalBounds().intersects(player.getPlayerSprite().getGlobalBounds())) // обработка столкновений врага и игрока
    {
        std::cout << "Collision detected!" << std::endl;
    }

    for (int i = 0; i < player.bullets.size(); i++) // обработка столкновений пуль и врага
    {
        if (sprite.getGlobalBounds().intersects(player.bullets[i].getGlobalBounds()))
        {
            std::cout << "PP" << std::endl;
            boundingRectangle.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
        }
        else
            boundingRectangle.setOutlineColor(sf::Color::Red);
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
}
