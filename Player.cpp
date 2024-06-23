#include "Player.h"
#include<iostream>
#include"Constans.h"

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent); // контур
    boundingRectangle.setOutlineColor(sf::Color::Blue);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(64, 64); // размер персонажа
}

//слежка за курсором 
sf::Vector2f Player::BulletWatch(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionWindow = window.mapPixelToCoords(mousePosition); // преобразование 2i к 2f *не знаю нах, но пусть будет*

    return mousePositionWindow;
}

void Player::Load() // загрузка персонажа
{
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png")) // загрузка текстурки
    {
        std::cout << "player loaded" << std::endl;
        sprite.setTexture(texture);// передача в спрайт текстуры игрока
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры игрока
        sprite.setPosition(sf::Vector2f(1650, 800));

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер персонажа
        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y)); // утсановка размера контура
    }
    else
        std::cout << "we have a problem";
}

sf::Sprite Player::getPlayerSprite() // геттер для спрайта
{
    return sprite;
}

sf::RectangleShape Player::getBullet()
{
    if(!bullets.empty())
        return bullets.back();
}

void Player::Update(sf::Event& event, sf::RenderWindow& window)  // движение персонажа
{
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // время с момента запуска таймера для анимации
    float timeForBullets = clockForBullets.getElapsedTime().asSeconds(); // время с момента запуска таймера для пуль

    // флаги для движения персонажа
    bool isMovingUp = false;
    bool isMovingLeft = false;
    bool isMovingDown = false;
    bool isMovingRight = false;

    // управление пулями
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeForBullets > bulletsSpeed) // утановка позиции пули
    {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(15, 15))); // добавление новой пули в вектор
        bullets[bullets.size() - 1].setPosition(sprite.getPosition() + sf::Vector2f(80, 64));
        direction = BulletWatch(window) - bullets[bullets.size() - 1].getPosition(); // направление выстрела
        direction = Math::NormalizeVector(direction); // нормализация вектора
        bulletsDirection.push_back(direction); // добавление в вектор позиции курсора
    }

    for (size_t i = 0; i < bullets.size(); i++) // отрисовка стрельбы
    {
        bullets[i].setPosition(bullets[i].getPosition() + bulletsDirection[i] * bulletSpeed); // установка поцизии пули
    }

    if (timeForBullets > bulletsSpeed)
        clockForBullets.restart();

    // управление персонажем
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        isMovingUp = true;
    else
        isMovingUp = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        isMovingDown = true;
    else
        isMovingDown = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        isMovingLeft = true;
    else
        isMovingLeft = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        isMovingRight = true;
    else
        isMovingRight = false;

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
        }
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
        {
            sprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
        }
    }

    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
        clockForAnimation.restart();

    sf::Vector2f movement(0, 0);
    if (isMovingUp)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y -= 3;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 0, 64, 64));
    }
    if (isMovingDown)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y += 3;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 128, 64, 64));
    }
    if (isMovingLeft)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x -= 3;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 64, 64, 64));
    }
    if (isMovingRight)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x += 3;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 196, 64, 64));
    }

    sprite.move(movement);
    boundingRectangle.setPosition(sprite.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
    for (size_t i = 0; i < bullets.size(); i++)
        window.draw(bullets[i]);
}

