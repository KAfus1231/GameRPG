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
    hitbox.setSize(sf::Vector2f(45, 50)); // размер хитбокса

    // рамка для hp
    boundingRectangleForHP.setFillColor(sf::Color::Transparent); 
    boundingRectangleForHP.setOutlineColor(sf::Color::White);
    boundingRectangleForHP.setOutlineThickness(1);
    boundingRectangleForHP.setSize(sf::Vector2f(60, 10));

    // полоска hp
    rectangleForHP.setFillColor(sf::Color::Red);
    rectangleForHP.setSize(sf::Vector2f(60, 10));

    // полоска дэша
    rectangleForDash.setFillColor(sf::Color::White);
    rectangleForDash.setSize(sf::Vector2f(60, 5));

    size = sf::Vector2i(96, 96); // размер персонажа
    view.reset(sf::FloatRect(0, 0, 1920, 1080)); // обзор камеры
}

void Player::Load() // загрузка персонажа
{
    try
    {
        texture.loadFromFile("Assets/Player/Textures/playerBlue.png"); // загрузка текстурки
        std::cout << "player loaded" << std::endl;

        sprite.setTexture(texture);// передача в спрайт текстуры игрока
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры игрока
        hitbox.setPosition(sf::Vector2f(1000, 670));

        if (!(texture.loadFromFile("Assets/Player/Textures/playerBlue.png")))
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
   /* sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionWindow = window.mapPixelToCoords(mousePosition);*/ // преобразование 2i к 2f *не знаю нах, но пусть будет*

    if (isShooting)
    {
        shootAnimationTime += deltaTime;
        if (shootAnimationTime > 80)
        {
            shootAnimationTime = 0;
            shootingFrame++;
        }
        if (shootingFrame >= 3)
            shootingFrame = 0;

        sprite.setTextureRect(sf::IntRect(96 * shootingFrame, 384, 96, 96));
    }
    
    if (timeForBullets > 0.3)
    {
        isShooting = false;

        if (timeForBullets > reloadingSpeed) // перезарядка ствола
            isReloading = false;
    }

    // управление пулями
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isReloading) // утановка позиции пули
    { 
        sf::RectangleShape bullet = sf::RectangleShape(sf::Vector2f(15, 15));
        bullet.setFillColor(sf::Color::Blue);
        bullets.push_back(bullet); // добавление новой пули в вектор
        bullets[bullets.size() - 1].setPosition(hitbox.getPosition() + sf::Vector2f(22.5, 25));
        /*bulletDirection = mousePositionWindow - bullets[bullets.size() - 1].getPosition();*/ // направление выстрела
        
        bulletDirection = Math::NormalizeVector(bulletDirection); // нормализация вектора
        bulletsDirection.push_back(bulletDirection); // добавление в вектор позиции курсора

        isShooting = true; // флаг стрельбы
        isReloading = true; // флаг перезарядки

        /*hitbox.move(-bulletDirection * deltaTime * playerSpeed * 12.0f);*/

        clockForBullets.restart();
    }
    
    for (size_t i = 0; i < bullets.size(); i++) // отрисовка стрельбы
    {
        bullets[i].setPosition(bullets[i].getPosition() + bulletsDirection[i] * bulletSpeed * deltaTime); // установка поцизии пули
    }
}
// метод передвижения 
void Player::movement(sf::Event& event, float deltaTime, Map& map, std::vector<Enemy>& enemies)
{
    sf::Vector2f movement(0, 0); // вектор нормали
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // время с момента запуска таймера для анимации
    playerSpeed = isShooting ? 0.0f : 0.2f; // определение скорости игрока

    sprite.setPosition(hitbox.getPosition().x + // ->
        (45 - sprite.getGlobalBounds().width) / 2, hitbox.getPosition().y - sprite.getGlobalBounds().height + 50);

    //установка спрайта персонажа
    if (bulletDirection.x >= 0)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
        sprite.setOrigin(96, 0);
        sprite.setScale(-1, 1);
    }

    // проверка столкновений
    if (collisions(enemies, map, deltaTime))
        return;

    // флаги для движения персонажа
    isMovingUp = false;
    isMovingLeft = false;
    isMovingDown = false;
    isMovingRight = false;

    // управление персонажем
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isShooting)
    {
        isMovingUp = true;
        isMovingDown = false;
    }
    else
        isMovingUp = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isShooting)
    {
        isMovingDown = true;
        isMovingUp = false;
    }
    else
        isMovingDown = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isShooting)
    {
        isMovingLeft = true;
        isMovingRight = false;
    }
    else
        isMovingLeft = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isShooting)
    {
        isMovingRight = true;
        isMovingLeft = false;
    }
    else
        isMovingRight = false;

    if ((isMovingDown || isMovingUp) && (isMovingLeft || isMovingRight))
    {
        frameSpeed = 0.1;
    }
    else
    {
        frameSpeed = 0.2;
    }

    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
        clockForAnimation.restart();

    if (isMovingUp) // движение вверх
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        movement.y -= 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 288, 96, 96));
    }
    if (isMovingDown) // движение вниз
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        movement.y += 3 * playerSpeed * deltaTime;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 288, 96, 96));
    }
    if (isMovingRight) // движение вправо
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        movement.x += 3 * playerSpeed * deltaTime;
        bulletDirection = sf::Vector2f(1, 0);
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 288, 96, 96));
        sprite.setOrigin(0, 0);
        sprite.setScale(1, 1);
    }
    if (isMovingLeft) // движение влево
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        movement.x -= 3 * playerSpeed * deltaTime;
        bulletDirection = sf::Vector2f(-1, 0);
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 288, 96, 96));
        sprite.setOrigin(96, 0);
        sprite.setScale(-1, 1);
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
    if (!reloadDash && isDash && isMovingLeft && dashEnergy > 0) // рывок влево
    {
        movement.x -= 30 * playerSpeed * 0.2 * deltaTime;
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
bool Player::collisions(std::vector<Enemy>& enemies, Map& map, float deltaTime)
{
    float timeForCollision = clockForCollision.getElapsedTime().asSeconds(); // таймер для столкновений
    float bounceForce = isDash ? 2.0f : 1.0f;
    bool isCollision = false;
    bool isEnemyCollision = false;
    playerDirection = sf::Vector2f(0, 0); // направление игрока по умолчанию равно 0       

    if (timeForCollision >= 0.7)
        clockForCollision.restart();

    for (const auto& mapHitbox : map.mapHitbox) {
        for(size_t i = 0; i < enemies.size(); i ++)
        {
            //столкновение игрока и врага
            if (hitbox.getGlobalBounds().intersects(enemies[i].getEnemySprite().getGlobalBounds()) && !enemies[i].getEnemyIsDead())
            {
                health -= 10;
                hitbox.move(enemies[i].getEnemyDirection() * deltaTime * bounceForce * 5.0f);
                isEnemyCollision = true;
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
            if (hitbox.getGlobalBounds().intersects(mapHitbox.getGlobalBounds()))
            {
                isCollision = true;
                playerDirection = sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2) -
                    sf::Vector2f(mapHitbox.getPosition().x + mapHitbox.getSize().x / 2, mapHitbox.getPosition().y + mapHitbox.getSize().y / 2); // вектор столкновения игрока и объекта
                playerDirection = Math::NormalizeVector(playerDirection); // нормализация вектора столкновения

                if (isEnemyCollision)
                {
                    hitbox.move(-enemies[i].getEnemyDirection().x * bounceForce * deltaTime * 14.0f, -enemies[i].getEnemyDirection().y * bounceForce * deltaTime * 14.0f);
                    enemies[i].discardEnemy(deltaTime, bounceForce);
                }

                hitbox.move(playerDirection * deltaTime);
            }
        }

        // столкновение пули с объектами карты
        for (const auto& bullet: bullets)
        {
            if (bullet.getGlobalBounds().intersects(mapHitbox.getGlobalBounds()))
            {
                bullets.erase(bullets.begin());
                bulletsDirection.erase(bulletsDirection.begin());
            }
        }
    }
    return isCollision;
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
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция полоски hp
    rectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция рамки дэша
    rectangleForDash.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height + 12);
}

void Player::Update(sf::Event& event, sf::RenderWindow& window, float deltaTime, std::vector<Enemy>& enemies, Map& map)  // обновление персонажа
{
    if (health > 0)
    {
        view = camera(view);
        /*collisions(enemies, map, deltaTime);*/
        movement(event, deltaTime, map, enemies);
        shoot(window, deltaTime);
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