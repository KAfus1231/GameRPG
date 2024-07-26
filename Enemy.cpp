#include"Enemy.h"
#include<iostream>
#include"Constans.h"

Enemy::Enemy() : health(100)
{

}

Enemy::~Enemy()
{
}


void Enemy::Initialize() {
    // хитбокс
    hitbox.setFillColor(sf::Color::Transparent); // контур
    hitbox.setOutlineColor(sf::Color::Red); // цвет контура
    hitbox.setOutlineThickness(1); // толщина контура

    // рамка для hp
    boundingRectangleForHP.setFillColor(sf::Color::Transparent);
    boundingRectangleForHP.setOutlineColor(sf::Color::White);
    boundingRectangleForHP.setOutlineThickness(1);
    boundingRectangleForHP.setSize(sf::Vector2f(76, 10));

    // полоска hp
    rectangleForHP.setFillColor(sf::Color::Red);
    rectangleForHP.setSize(sf::Vector2f(76, 10));

    size = sf::Vector2i(64, 64); // размер врага
}

void Enemy::Load()
{
    try
    {
        texture.loadFromFile("Assets/Enemy/Textures/spritesheetEnemy.png"); // загрузка текстурки
        std::cout << "enemy loaded" << std::endl;

        sprite.setTexture(texture);// врага
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры врага

        sprite.scale(sf::Vector2f(2.0, 2.0)); // размер скелета
        hitbox.setSize(sf::Vector2f(70, 100)); // утсановка размера контура
        hitbox.setPosition(sf::Vector2f(400, 700));

        sprites.push_back(sprite); // добавление спрайта в вектор

        if (!(texture.loadFromFile("Assets/Enemy/Textures/spritesheetEnemy.png")))
            throw "void Enemy::Load()";
    }
    catch(const char* errMsg)
    {
        std::cerr << "Problem:" << errMsg << std::endl; // ловлю ошибку
    }
}

// метод движения врага
void Enemy::movement(Player& player, float deltaTime)
{
    float timeForAnimation = clockForAnimation.getElapsedTime().asSeconds(); // таймер для смены анимаций

    direction = player.getHitbox().getPosition() - hitbox.getPosition(); // направление для движения врага
    direction = Math::NormalizeVector(direction); // нормализация

    hitbox.setPosition(hitbox.getPosition() + direction * deltaTime * EnemySpeed); // устоновка поцизии врага (бегает за игроком)
    sprites[spritesNumber].setPosition(hitbox.getPosition().x + // ->
        (70 - sprites[spritesNumber].getGlobalBounds().width) / 2, hitbox.getPosition().y - sprites[spritesNumber].getGlobalBounds().height + 100);

    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
        clockForAnimation.restart();

    if (direction.y < 0)
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
}
// метод обработки столкновений
void Enemy::collisions(Player& player, Map & map, float deltaTime)
{
    // попадание пули во врага
    for (int i = 0; i < player.bullets.size(); i++) // обработка столкновений пуль и врага
    {
        if (hitbox.getGlobalBounds().intersects(player.bullets[i].getGlobalBounds()))
        {
            health -= 10;
            hitbox.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
            player.bullets.erase(player.bullets.begin() + i); // удаление пули при попадании во врага
            player.bulletsDirection.erase(player.bulletsDirection.begin() + i); // удаление направления пули при попадании во врага
            rectangleForHP.setSize(rectangleForHP.getSize() - sf::Vector2f(7.6, 0)); // уменьшение полоски hp при попадании 
        }
        else
            hitbox.setOutlineColor(sf::Color::Red);
    }

    // столкновение с объектами карты
    for (size_t i = 0; i < map.mapObjects.size(); i++)
    {
        if (hitbox.getGlobalBounds().intersects(map.mapObjects[i].getGlobalBounds()))
        {
            collisionDirection = hitbox.getPosition() - map.mapObjects[i].getPosition();
            collisionDirection = Math::NormalizeVector(collisionDirection);

            hitbox.move(collisionDirection.x * 8, collisionDirection.y * 8);
        }
    }

}
// метод вывода информации над врагом
void Enemy::status()
{
    // позиция рамки для hp
    boundingRectangleForHP.setPosition(sprites[spritesNumber].getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprites[spritesNumber].getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция полоски hp
    rectangleForHP.setPosition(sprites[spritesNumber].getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprites[spritesNumber].getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
}
// метод обработки смерти врага
void Enemy::death()
{
    health = 100; // hp снова 100
    rectangleForHP.setSize(sf::Vector2f(76, 10)); // размер полоски hp снова полный
    spritesNumber += 1; // переход к следующему спрайту
    sprites.push_back(sprite);

    int spawn = std::rand() % 4;
    switch (spawn)
    {
    case 0: 
        hitbox.setPosition(sf::Vector2f(170, 170)); 
        break;
    case 1: 
        hitbox.setPosition(sf::Vector2f(170, 1000));
        break;
    case 2:
        hitbox.setPosition(sf::Vector2f(1800, 170)); 
        break;
    case 3: 
        hitbox.setPosition(sf::Vector2f(1800, 1000));
        break;
    }
}
// отбрасывание врага при столкновении
void Enemy::discardEnemy(float deltaTime, float bounceForce)
{
    hitbox.move(-direction * deltaTime * bounceForce * 3.0f);
}

void Enemy::Update(Player& player, float deltaTime, Map& map)
{
    if(health > 0)
    {
        movement(player, deltaTime);
        collisions(player, map, deltaTime);
        status();
    }
    else // если hp стало 0
    {
        death();
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.draw(sprites[spritesNumber]);
        window.draw(hitbox);
        window.draw(rectangleForHP);
        window.draw(boundingRectangleForHP);
    }
}

sf::Vector2f Enemy::getEnemyDirection()
{
    return direction;
}

sf::Sprite Enemy::getEnemySprite() // геттер для спрайта
{
    return sprites[spritesNumber];
}

sf::RectangleShape Enemy::getEnemyHitbox()
{
    return hitbox;
}
