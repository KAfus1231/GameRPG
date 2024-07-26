#include "Math.h"

sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    // Проверка на нулевой вектор
    if (m == 0) {
        // Возвращаем нулевой вектор или обработаем этот случай по-другому
        return sf::Vector2f(0, 0); // Или выбросите исключение, если нужно
    }

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;

    return normalizedVector;
}
