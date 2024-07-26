#include "Math.h"

sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    // �������� �� ������� ������
    if (m == 0) {
        // ���������� ������� ������ ��� ���������� ���� ������ ��-�������
        return sf::Vector2f(0, 0); // ��� ��������� ����������, ���� �����
    }

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;

    return normalizedVector;
}
