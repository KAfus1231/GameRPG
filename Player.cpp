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
    hitbox.setFillColor(sf::Color::Transparent); // контур
    hitbox.setOutlineColor(sf::Color::Blue); // цвет контура 
    hitbox.setOutlineThickness(1); // толщина
    hitbox.setSize(sf::Vector2f(70, 100)); // размер хитбокса

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
        hitbox.setPosition(sf::Vector2f(1000, 670));

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер персонажа
        
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
        bullets[bullets.size() - 1].setPosition(hitbox.getPosition() + sf::Vector2f(35, 50));
        bulletDirection = mousePositionWindow - bullets[bullets.size() - 1].getPosition(); // направление выстрела
        bulletDirection = Math::NormalizeVector(bulletDirection); // нормализация вектора
        bulletsDirection.push_back(bulletDirection); // добавление в вектор позиции курсора
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
    sf::Vector2f movement(0, 0); // вектор нормали
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // время с момента запуска таймера для анимации
    sprite.setPosition(hitbox.getPosition().x + // ->
        (70 - sprite.getGlobalBounds().width) / 2, hitbox.getPosition().y - sprite.getGlobalBounds().height + 100);

    // флаги для движения персонажа
    isMovingUp = false;
    isMovingLeft = false;
    isMovingDown = false;
    isMovingRight = false;

    // управление персонажем
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        isMovingUp = true;
        isMovingDown = false;
    }
    else
        isMovingUp = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        isMovingDown = true;
        isMovingUp = false;
    }
    else
        isMovingDown = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        isMovingLeft = true;
        isMovingRight = false;
    }
    else
        isMovingLeft = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        isMovingRight = true;
        isMovingLeft = false;
    }
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

    if (isMovingUp) // движение вверх
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y -= 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 0, 64, 64));
    }
    if (isMovingDown) // движение вниз
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.y += 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 128, 64, 64));
    }
    if (isMovingLeft) // движение влево
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x -= 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 64, 64, 64));
    }
    if (isMovingRight) // движение вправо
    {
        frame += timeForAnimation;
        if (frame > 9)
            frame = 0;
        movement.x += 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(64 * int(frame), 196, 64, 64));
    }

    //---------------------------------------------ДЭШ-----------------------------------------------
    isDash = false;
    float timerForDash = clockForDash.getElapsedTime().asSeconds();

    if (dashEnergy == 0)
        reloadDash = true;

    if (reloadDash && dashEnergy < 100)
        reloadDash = true;

    else if (reloadDash && dashEnergy == 100)
        reloadDash = false;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !reloadDash) // дэш по нажатии на SHift
        isDash = true;
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
    hitbox.move(movement); // движение игрока
}
// метод обработки столкновений
void Player::collisions(std::vector<Enemy>& enemies, Map& map, float deltaTime)
{
    float timeForCollision = clockForCollision.getElapsedTime().asSeconds(); // таймер для столкновений
    float bounceForce = isDash ? 4.0f : 2.0f;
    bool isCollision = false;

    if (timeForCollision >= 0.7)
        clockForCollision.restart();

    for (const auto& mapObject : map.mapObjects) {
        for(size_t i = 0; i < enemies.size(); i ++)
        {
            //столкновение игрока и врага  
            playerDirection = sf::Vector2f(0, 0); // направление игрока по умолчанию равно 0       

            if (hitbox.getGlobalBounds().intersects(enemies[i].getEnemySprite().getGlobalBounds()) && !enemies[i].getEnemyIsDead())
            {
                /*health -= 10;*/
                hitbox.move(enemies[i].getEnemyDirection() * deltaTime * bounceForce * 5.0f);
                /*enemy.discardEnemy(deltaTime, bounceForce);*/
                isCollision = true;
                if (timeForCollision < 0.7)
                {
                    sprite.setColor(sf::Color::Red);
                    hitbox.setOutlineColor(sf::Color::Red);
                }

                rectangleForHP.setSize(rectangleForHP.getSize() - sf::Vector2f(7.6, 0)); // уменьшение полоски hp при попадании 
            }

            if (timeForCollision >= 0.7)
            {
                sprite.setColor(sf::Color::White);
                hitbox.setOutlineColor(sf::Color::Blue);
            }

            //столкновение игрока с объектами карты
            if (hitbox.getGlobalBounds().intersects(mapObject.getGlobalBounds()))
            {
                std::cout << "Collision" << std::endl;
                playerDirection = hitbox.getPosition() - mapObject.getPosition(); // вектор столкновения игрока и объекта
                playerDirection = Math::NormalizeVector(playerDirection); // нормализация вектора столкновения

                if (isCollision)
                {
                    hitbox.move(-enemies[i].getEnemyDirection().x * bounceForce * deltaTime * 14.0f, -enemies[i].getEnemyDirection().y * bounceForce * deltaTime * 14.0f);
                    enemies[i].discardEnemy(deltaTime, bounceForce);
                }

                hitbox.move(playerDirection.x * bounceForce * deltaTime, playerDirection.y * bounceForce * deltaTime);
            }
        }

        // столкновение пули с объектами карты
        for (const auto& bullet: bullets)
        {
            if (bullet.getGlobalBounds().intersects(mapObject.getGlobalBounds()))
            {
                bullets.erase(bullets.begin());
                bulletsDirection.erase(bulletsDirection.begin());
            }
        }
    }
}
// измерение скорости персонажа
sf::Vector2f Player::getPlayerSpeed(float deltaTime)
{
    sf::Vector2f currentPosition = hitbox.getPosition();
    
    if (clockForSpeed.getElapsedTime().asSeconds() >= 0.1f)
    {
        sf::Vector2f speed = (currentPosition - previousPosition) / deltaTime;

        previousPosition = currentPosition;

        clockForSpeed.restart();

        return sf::Vector2f(std::abs(speed.x), std::abs(speed.y));
    }
    else
        return sf::Vector2f(0, 0);
        
}

// метода камеры
sf::View Player::camera(sf::View view)
{
    view.setCenter(hitbox.getPosition().x, hitbox.getPosition().y);
    return view;
}
// статус игрока
void Player::status()
{
    // позиция рамки для hp
    boundingRectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height + 10);
    // позиция полоски hp
    rectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height + 10);
    // позиция рамки дэша
    rectangleForDash.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height + 24);
}

void Player::Update(sf::Event& event, sf::RenderWindow& window, float deltaTime, std::vector<Enemy>& enemies, Map& map)  // обновление персонажа
{
    if (health > 0)
    {
        view = camera(view);
        shoot(window, deltaTime);
        collisions(enemies, map, deltaTime);
        movement(event, deltaTime);
        status();
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.setView(view);
        window.draw(sprite);
        window.draw(hitbox);
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

sf::RectangleShape Player::getHitbox()
{
    return hitbox;
}