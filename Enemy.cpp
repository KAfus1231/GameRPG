#include "Enemy.h"
#include<iostream>
#include"Constans.h"

sf::Sprite Enemy::getEnemySprite()
{
    return sprite;
}

void Enemy::Initialize()
{
}

void Enemy::Load()
{
    if (texture.loadFromFile("Assets/Enemy/Textures/spritesheetEnemy.png")) // загрузка текстурки
    {
        std::cout << "enemy loaded" << std::endl;
        sprite.setTexture(texture);// врага

        sprite.setTextureRect(sf::IntRect(0, 128, 64, 64)); // выбор текстуры врага
        sprite.scale(sf::Vector2f(3.0, 3.0)); // размер врага
        sprite.setPosition(sf::Vector2f(400, 700));
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update()
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
