#include"Enemy.h"
#include<iostream>
#include"Constans.h"

Enemy::Enemy() : health(100)
{
    Initialize();
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

    size = sf::Vector2i(96, 96); // размер врага
}

void Enemy::Load(Map &map)
{
    try
    {
        if (!(texture.loadFromFile("Assets/Enemy/Textures/enemies x3.png")))
            throw "void Enemy::Load()";

        textureForDeath.loadFromFile("Assets/Enemy/Textures/enemies x3.png"); // текстурка для гибели

        std::cout << "enemy loaded" << std::endl;

        spriteForDeath.setTexture(textureForDeath);
        spriteForDeath.setTextureRect(sf::IntRect(0, 0, size.x, size.y));

        sprite.setTexture(texture);// врага
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y)); // выбор текстуры врага

        hitbox.setSize(sf::Vector2f(45, 50)); // утсановка размера контура

        hitbox.setPosition(map.getEnemyStartPosition());
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

    sf::Vector2f spritePosition = sf::Vector2f(hitbox.getPosition().x + // ->
        (45 - sprite.getGlobalBounds().width) / 2, hitbox.getPosition().y - sprite.getGlobalBounds().height + 80);

    sprite.setPosition(spritePosition);

    if(fieldOfView(deltaTime, player))
        hitbox.setPosition(hitbox.getPosition() + direction * deltaTime * EnemySpeed); // устоновка поцизии врага (бегает за игроком)

    if (timeForAnimation > frameSpeed) // перезапуск таймера если время превысило заданное 
        clockForAnimation.restart();

    if (direction.y < 0)
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 0, 96, 96));
    }
    if (direction.y > 0)
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 0, 96, 96));
    }
    if (direction.x < 0) 
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 0, 96, 96));
        sprite.setOrigin(96, 0);
        sprite.setScale(-1, 1);
    }
    if (direction.x > 0)
    {
        frame += timeForAnimation;
        if (frame > 3)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(96 * int(frame), 0, 96, 96));
        sprite.setOrigin(0, 0);
        sprite.setScale(1, 1);
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
            collisionDirection = hitbox.getPosition() - player.bullets[i].getPosition();
            collisionDirection = Math::NormalizeVector(collisionDirection);
            hitbox.move(collisionDirection.x * 8, collisionDirection.y * 8);

            hitbox.setOutlineColor(sf::Color::Yellow); // при попадании установка желтого цвета рамки
            player.bullets.erase(player.bullets.begin() + i); // удаление пули при попадании во врага
            player.bulletsDirection.erase(player.bulletsDirection.begin() + i); // удаление направления пули при попадании во врага
            rectangleForHP.setSize(rectangleForHP.getSize() - sf::Vector2f(7.6, 0)); // уменьшение полоски hp при попадании 
        }
        else
            hitbox.setOutlineColor(sf::Color::Red);
    }

    // столкновение с объектами карты
    for (size_t i = 0; i < map.mapHitbox.size(); i++)
    {
        if (hitbox.getGlobalBounds().intersects(map.mapHitbox[i].getGlobalBounds()))
        {
            collisionDirection = sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2) -
                sf::Vector2f(map.mapHitbox[i].getPosition().x + map.mapHitbox[i].getSize().x / 2, map.mapHitbox[i].getPosition().y + map.mapHitbox[i].getSize().y / 2);
            collisionDirection = Math::NormalizeVector(collisionDirection);

            hitbox.move(collisionDirection.x * 8, collisionDirection.y * 8);
        }
    }

}
// метод вывода информации над врагом
void Enemy::status()
{
    // позиция рамки для hp
    boundingRectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
    // позиция полоски hp
    rectangleForHP.setPosition(sprite.getPosition().x + // ->
        (128 - boundingRectangleForHP.getGlobalBounds().width) / 2, sprite.getPosition().y - boundingRectangleForHP.getGlobalBounds().height);
}
// метод обработки смерти врага
void Enemy::death()
{
    isDead = true;
    deathPosition = sprite.getPosition(); // позиция проигрывания анимации смерти
}
// анимация смерти врага
void Enemy::enemyDeathAnimation(float deltaTime)
{
    spriteForDeath.setPosition(deathPosition);
   
    deathAnimationTime += deltaTime;

    if (deathAnimationTime > frameDeathSpeed)
    {
        deathAnimationTime = 0;
        currentDeathFrame++;
    }

    if (currentDeathFrame >= 7)
    {
        deathAnimationComplete = true;
        return;
    }
    if(direction.x < 0) // если повернут, анимация тоже поворачивается
    {
        spriteForDeath.setTextureRect(sf::IntRect(96 * int(currentDeathFrame), 288, 96, 96));
        spriteForDeath.setOrigin(96, 0);
        spriteForDeath.setScale(-1, 1);
    }
    else
        spriteForDeath.setTextureRect(sf::IntRect(96 * int(currentDeathFrame), 288, 96, 96));
}
// метод обзора
bool Enemy::fieldOfView(float deltaTime, Player& player)
{
    float timeForViewing = clockForView.getElapsedTime().asSeconds(); // таймер для фиксации обзора
    
    view.setSize(sf::Vector2f(350, 350)); // по умолчанию размер 
    view.setOrigin(175, 175);

    if(inTheViewing) // если игрок попал в обзор, то обзор на время становится больше
    {
        view.setSize(sf::Vector2f(500, 500));
        view.setOrigin(250, 250);
    }
    // установка позиции обзора
    view.setPosition(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2);
    view.setFillColor(sf::Color::Transparent); view.setOutlineColor(sf::Color::Green); view.setOutlineThickness(2);

    if (view.getGlobalBounds().intersects(player.getHitbox().getGlobalBounds())) // если игрок попал в квадрат обзора, то срабатывает флаг
    {
        clockForView.restart();

        inTheViewing = true;
        std::cout << inTheViewing << std::endl;
    }
    else if (timeForViewing >= 5)
    {
        inTheViewing = false;
    }

    return inTheViewing; // сам флаг
}

void Enemy::Update(Player& player, float deltaTime, Map& map)
{
    if(health > 0)
    {
        fieldOfView(deltaTime, player);
        movement(player, deltaTime);
        collisions(player, map, deltaTime);
        status();
    }
    else
    {
        death();
        if(!deathAnimationComplete) // пока анимация не выполнена, вызывается метод обработки смерти
            enemyDeathAnimation(deltaTime);
    }
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if(health > 0)
    {
        window.draw(sprite);
        window.draw(hitbox);
        window.draw(rectangleForHP);
        window.draw(boundingRectangleForHP);
        window.draw(view);
    }
    else if(!deathAnimationComplete)
        window.draw(spriteForDeath);
}

sf::Vector2f Enemy::getEnemyDirection()
{
    return direction;
}

// отбрасывание врага при столкновении
void Enemy::discardEnemy(float deltaTime, float bounceForce)
{
    hitbox.move(-direction * deltaTime * bounceForce * 3.0f);
}

sf::Sprite Enemy::getEnemySprite() // геттер для спрайта
{
    return sprite;
}

sf::RectangleShape Enemy::getEnemyHitbox()
{
    return hitbox;
}

bool Enemy::getEnemyIsDead()
{
    return isDead;
}
