#include "Enemy.h"
#include<iostream>
#include"Constans.h"

sf::Sprite Enemy::getEnemySprite() // геттер для спрайта
{
    return sprite;
}

void Enemy::Initialize() {
    boundingRectangle.setFillColor(sf::Color::Transparent); // контур
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64); // размер врага
}

void Enemy::Load()
{
    if (texture.loadFromFile("Assets/Enemy/Textures/spritesheetEnemy.png")) // загрузка текстурки
    {
        std::cout << "enemy loaded" << std::endl;
        sprite.setTexture(texture);// врага

        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры врага
        sprite.setPosition(sf::Vector2f(400, 700));

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер скелета
        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y)); // утсановка размера контура
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update(Player& player)
{
    sf::Vector2f direction = player.getPlayerSprite().getPosition() - sprite.getPosition();
    direction = Math::NormalizeVector(direction);
    sprite.setPosition(sprite.getPosition() + direction * bulletSpeed);

    boundingRectangle.setPosition(sprite.getPosition());
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
}
