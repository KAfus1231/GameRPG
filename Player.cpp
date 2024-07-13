#include "Player.h"
#include<iostream>
#include"Constans.h"
#include "Enemy.h"

Player::Player() : health(100) , dashEnergy(100)
{

}

Player::~Player()
{

}
            
void Player::Initialize()
{
    // хитбокс
    boundingRectangle.setFillColor(sf::Color::Transparent); // контур
    boundingRectangle.setOutlineColor(sf::Color::Blue); // цвет контура 
    boundingRectangle.setOutlineThickness(1); // толщина

    // рамка для hp
    boundingRectangleForHP.setFillColor(sf::Color::Transparent); 
    boundingRectangleForHP.setOutlineColor(sf::Color::White);
    boundingRectangleForHP.setOutlineThickness(1);
    boundingRectangleForHP.setSize(sf::Vector2f(76, 10));

    // полоска hp
    rectangleForHP.setFillColor(sf::Color::Red);
    rectangleForHP.setSize(sf::Vector2f(76, 10));

    // полоска дэша
    rectangleForDash.setFillColor(sf::Color::White);
    rectangleForDash.setSize(sf::Vector2f(76, 5));

    size = sf::Vector2i(64, 64); // размер персонажа
    view.reset(sf::FloatRect(0, 0, 1920, 1080)); // обзор камеры
}

void Player::Load() // загрузка персонажа
{
    try
    {
        texture.loadFromFile("Assets/Player/Textures/spritesheet.png"); // загрузка текстурки
        std::cout << "player loaded" << std::endl;

        sprite.setTexture(texture);// передача в спрайт текстуры игрока
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры игрока
        sprite.setPosition(sf::Vector2f(1650, 800));

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер персонажа
        boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y)); // утсановка размера контура

        if (!(texture.loadFromFile("Assets/Player/Textures/spritesheet.png")))
            throw "void Player::Load()";
    }
    catch (const char* errMsg)
    {
        std::cerr << "Problem:" << errMsg << std::endl; // ловлю ошибку
    }
}

// метод стрельбы
void Player::shoot(sf::RenderWindow& window, float deltaTime)
{
    float timeForBullets = clockForBullets.getElapsedTime().asSeconds(); // время с момента запуска таймера для пуль
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionWindow = window.mapPixelToCoords(mousePosition); // преобразование 2i к 2f *не знаю нах, но пусть будет*

    // управление пулями
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeForBullets > bulletsSpeed) // утановка позиции пули
    {
        bullets.push_back(sf::RectangleShape(sf::Vector2f(15, 15))); // добавление новой пули в вектор
        bullets[bullets.size() - 1].setPosition(sprite.getPosition() + sf::Vector2f(80, 64));
        direction = mousePositionWindow - bullets[bullets.size() - 1].getPosition(); // направление выстрела
        direction = Math::NormalizeVector(direction); // нормализация вектора
        bulletsDirection.push_back(direction); // добавление в вектор позиции курсора
    }

    for (size_t i = 0; i < bullets.size(); i++) // отрисовка стрельбы
    {
        bullets[i].setPosition(bullets[i].getPosition() + bulletsDirection[i] * bulletSpeed * deltaTime); // установка поцизии пули
    }

    if (timeForBullets > bulletsSpeed)
        clockForBullets.restart();
}
// метод передвижения 
void Player::movement(sf::Event& event, float deltaTime)
{
    sf::Vector2f movement(0, 0);
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // время с момента запуска таймера для анимации

    // флаги для движения персонажа
    bool isMovingUp = false;
    bool isMovingLeft = false;
    bool isMovingDown = false;
    bool isMovingRight = false;

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

    if (isMovingUp)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y -= 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 0, 64, 64));
    }
    if (isMovingDown)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y += 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 128, 64, 64));
    }
    if (isMovingLeft)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x -= 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 64, 64, 64));
    }
    if (isMovingRight)
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x += 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 196, 64, 64));
    }

    //---------------------------------------------ДЭШ-----------------------------------------------
    bool isDash = false;
    float timerForDash = clockForDash.getElapsedTime().asSeconds();

    if (dashEnergy == 0)
        reloadDash = true;

    if (reloadDash && dashEnergy < 100)
        reloadDash = true;

    else if (reloadDash && dashEnergy == 100)
        reloadDash = false;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !reloadDash) // дэш по нажатия на SHift
    {
        isDash = true;
    }
    else
        isDash == false;

    if (!reloadDash && isDash && isMovingUp && dashEnergy > 0) // рывок вверх
    {
        movement.y -= 30 * playerSpeed * 0.2 * deltaTime;
        dashEnergy -= 1;// уменьшаем энергию на 1
        rectangleForDash.setSize(rectangleForDash.getSize() - sf::Vector2f(0.76, 0)); // уменьшаем размер полосочки энергии
    }
    if (!reloadDash && isDash && isMovingLeft && dashEnergy > 0) // рывок влево
    {
        movement.x -= 30 * playerSpeed * 0.2 * deltaTime;
        dashEnergy -= 1;
        rectangleForDash.setSize(rectangleForDash.getSize() - sf::Vector2f(0.76, 0));
    }
    if (!reloadDash && isDash && isMovingRight && dashEnergy > 0) // рывок вправо
    {
        movement.x += 30 * playerSpeed * 0.2 * deltaTime;
        dashEnergy -= 1;
        rectangleForDash.setSize(rectangleForDash.getSize() - sf::Vector2f(0.76, 0));
    }
    if (!reloadDash && isDash && isMovingDown && dashEnergy > 0) // рывок вниз
    {
        movement.y += 30 * playerSpeed * 0.2 * deltaTime;
        dashEnergy -= 1;
        rectangleForDash.setSize(rectangleForDash.getSize() - sf::Vector2f(0.76, 0));
    }

    if (timerForDash > 0.03)
        clockForDash.restart();

    if (dashEnergy <= 100 && timerForDash >= 0.03 && !isDash)
    {
        dashEnergy += 1;
        rectangleForDash.setSize(rectangleForDash.getSize() + sf::Vector2f(0.76, 0));
    }
    sprite.move(movement); // движение игрока
}
// метод обработки столкновений
void Player::collisions(Enemy& enemy)
{
    float timeForCollision = clockForCollision.getElapsedTime().asSeconds(); // таймер для столкновений
    
    if (timeForCollision >= 0.7)
        clockForCollision.restart();
    //столкновение игрока и врага
    if (sprite.getGlobalBounds().intersects(enemy.getEnemySprite().getGlobalBounds()))
    {
        health -= 10;
        if (enemy.getEnemyDirection().x > 0) // удар слева
            sprite.setPosition(sprite.getPosition() + sf::Vector2f(100, 0));

        if (enemy.getEnemyDirection().x < 0) // удар справа
            sprite.setPosition(sprite.getPosition() - sf::Vector2f(100, 0));

        if (enemy.getEnemyDirection().y > 0) // удар сверху
            sprite.setPosition(sprite.getPosition() + sf::Vector2f(0, 100));

        if (enemy.getEnemyDirection().x > 0) // удар снизу
            sprite.setPosition(sprite.getPosition() - sf::Vector2f(0, 100));

        if (timeForCollision < 0.7)
        {
            sprite.setColor(sf::Color::Red);
            boundingRectangle.setOutlineColor(sf::Color::Red);
        }
        rectangleForHP.setSize(rectangleForHP.getSize() - sf::Vector2f(7.6, 0)); // уменьшение полоски hp при попадании 
    }
    else if (timeForCollision >= 0.7)
    {
        sprite.setColor(sf::Color::White);
        boundingRectangle.setOutlineColor(sf::Color::Blue);
    }
}
// метода камеры
sf::View Player::camera(sf::View view)
{
    view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
    return view;
}
// статус игрока
void Player::status()
{
    boundingRectangle.setPosition(sprite.getPosition()); // установка поции рамки
    // позиция рамки для hp
    boundingRectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция полоски hp
    rectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция рамки дэша
    rectangleForDash.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - rectangleForDash.getGlobalBounds().height + 6);
}

void Player::Update(sf::Event& event, sf::RenderWindow& window, float deltaTime, Enemy &enemy)  // обновление персонажа
{
    if (health > 0)
    {
        view = camera(view);
        shoot(window, deltaTime);
        movement(event, deltaTime);
        collisions(enemy);
        status();
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.setView(view);
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(rectangleForHP);
        window.draw(boundingRectangleForHP);

        if(dashEnergy < 100) // если энегрия дэша полная, то не рисуем его
            window.draw(rectangleForDash);

        for (size_t i = 0; i < bullets.size(); i++)
            window.draw(bullets[i]);
    }
    else
        window.close();
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
