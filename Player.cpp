#include "Player.h"
#include<iostream>
#include"Constans.h"

void Player::Initialize()
{
}

sf::Vector2f Player::NormalizeVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;

    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;

    return normalizedVector;
}

//������ �� �������� 
sf::Vector2f Player::BulletWatch(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionWindow = window.mapPixelToCoords(mousePosition); // �������������� 2i � 2f *�� ���� ���, �� ����� �����*

    return mousePositionWindow;
}

void Player::Load() // �������� ���������
{
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png")) // �������� ���������
    {
        std::cout << "player loaded" << std::endl;
        sprite.setTexture(texture);// �������� � ������ �������� ������

        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64)); // ����� �������� ������
        sprite.scale(sf::Vector2f(3.0, 3.0)); // ������ ���������
        sprite.setPosition(sf::Vector2f(1650, 800));
    }
    else
        std::cout << "we have a problem";
}

sf::Sprite Player::getPlayerSprite()
{
    return sprite;
}

void Player::Update(sf::Event& event, sf::RenderWindow& window)  // �������� ���������
{
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // ����� � ������� ������� ������� ��� ��������
    float timeForBullets = clockForBullets.getElapsedTime().asSeconds(); // ����� � ������� ������� ������� ��� ����

    // ����� ��� �������� ���������
    bool isMovingUp = false;
    bool isMovingLeft = false;
    bool isMovingDown = false;
    bool isMovingRight = false;

    // ���������� ������
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeForBullets > bulletsSpeed) // �������� ������� ����
    {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(15, 15))); // ���������� ����� ���� � ������
        bullets[bullets.size() - 1].setPosition(sprite.getPosition() + sf::Vector2f(80, 64));
        direction = BulletWatch(window) - bullets[bullets.size() - 1].getPosition(); // ����������� ��������
        direction = NormalizeVector(direction); // ������������ �������
        bulletsDirection.push_back(direction); // ���������� � ������ ������� �������
    }

    for (size_t i = 0; i < bullets.size(); i++) // ��������� ��������
    {
        bullets[i].setPosition(bullets[i].getPosition() + bulletsDirection[i] * bulletSpeed); // ��������� ������� ����
    }

    if (timeForBullets > bulletsSpeed)
        clockForBullets.restart();
    
    // ���������� ����������
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

    if (timeForAnimation > frameSpeed) // ���������� ������� ���� ����� ��������� �������� 
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
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (size_t i = 0; i < bullets.size(); i++)
        window.draw(bullets[i]);
}

//void Player::DrawBullet(sf::RenderWindow& window)
//{
//    for (size_t i = 0; i < bullets.size(); i++)
//        window.draw(bullets[i]);
//}