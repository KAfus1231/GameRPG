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
    }
    else
        std::cout << "Somthing wrong" << std::endl;
}

void Enemy::Update(Player& player, float deltaTime)
{
    if(health > 0)
    {
        sf::Vector2f direction = player.getPlayerSprite().getPosition() - sprite.getPosition(); // направление для движения врага
        direction = Math::NormalizeVector(direction); // нормализация
        sprite.setPosition(sprite.getPosition() + direction * deltaTime * EnemySpeed); // устоновка поцизии врага (бегает за игроком)

        boundingRectangle.setPosition(sprite.getPosition()); // рамка привязана к спрайту врага

        healthText.setString(std::to_string(health)); // установка полоски hp
        healthText.setPosition(sprite.getPosition().x + // ->
            (128 - healthText.getGlobalBounds().width) / 2, sprite.getPosition().y - healthText.getGlobalBounds().height); // установка позиции полоски hp

        if (sprite.getGlobalBounds().intersects(player.getPlayerSprite().getGlobalBounds())) // обработка столкновений врага и игрока
        {
            std::cout << "Collision detected!" << std::endl;
            player.boundingRectangle.setOutlineColor(sf::Color::Red);
        }
        else
            player.boundingRectangle.setOutlineColor(sf::Color::Blue);

        for (int i = 0; i < player.bullets.size(); i++) // обработка столкновений пуль и врага
        {
            if (sprite.getGlobalBounds().intersects(player.bullets[i].getGlobalBounds()))
            {
                health -= 10;
                std::cout << "Enemy Health is: " << health << std::endl;
                boundingRectangle.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
                player.bullets.erase(player.bullets.begin() + i); // удаление пули при попадании во врага
                player.bulletsDirection.erase(player.bulletsDirection.begin() + i); // удаление направления пули при попадании во врага

            }
            else
                boundingRectangle.setOutlineColor(sf::Color::Red);
        }
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(healthText);
    }
}
