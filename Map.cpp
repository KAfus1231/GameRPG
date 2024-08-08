#include "Map.h"
#include <iostream>

Map::Map() : tileWidth(16), tileHeight(16), totalTilesX(0), totalTilesY(0)
{
}

Map::~Map() {}

void Map::Initialize() // карта 
{
	// ПЕРВЫЙ СЛОЙ!!
	firstLayer[0] =  "                                   ";
	firstLayer[1] =  "                                   ";
	firstLayer[2] =  "                                   ";
	firstLayer[3] =  "                                   ";
	firstLayer[4] =  "   [-----------]                   ";
	firstLayer[5] =  "   |           |                   ";
	firstLayer[6] =  "   |00000000000{-----]             ";
	firstLayer[7] =  "   |00000000000      {--------]    ";
	firstLayer[8] =  " --}00000000000000000         |    ";
	firstLayer[9] =  "0   00000000000000000000000000|    ";
	firstLayer[10] = "000000000000000000000000000000|    ";
	firstLayer[11] = "0[__0000000[__0000000000000000|    ";
	firstLayer[12] = " |000000000|000000000000000000|    ";
	firstLayer[13] = " |000000000|000000000000000000|    ";
	firstLayer[14] = " <_________|000000000000000000|    ";
	firstLayer[15] = "           |000000000000000000|    ";
	firstLayer[16] = "           <__________________>    ";
	firstLayer[17] = "                                   ";
	firstLayer[18] = "                                   ";
	firstLayer[19] = "                                   ";

	// ВТОРОЙ СЛОЙ!!
	secondLayer[0] =  "                                   ";
	secondLayer[1] =  "                                   ";
	secondLayer[2] =  "                                   ";
	secondLayer[3] =  "                                   ";
	secondLayer[4] =  "   IIIIIIIIIIIII                   ";
	secondLayer[5] =  "   I           I                   ";
	secondLayer[6] =  "   I  S        IIIIIII             ";
	secondLayer[7] =  "   I                 IIIIIIIIII    ";
	secondLayer[8] =  " III          S               I    ";
	secondLayer[9] =  "S                             I    ";
	secondLayer[10] = "        S                     I    ";
	secondLayer[11] = " III       III         S      I    ";
	secondLayer[12] = " I         I                  I    ";
	secondLayer[13] = " I         I                  I    ";
	secondLayer[14] = " IIIIIIIIIII   S        S     I    ";
	secondLayer[15] = "           I                  I    ";
	secondLayer[16] = "           IIIIIIIIIIIIIIIIIIII    ";
	secondLayer[17] = "                                   ";
	secondLayer[18] = "                                   ";
	secondLayer[19] = "                                   ";

	// ТРЕТИЙ СЛОЙ!!ПОСЛЕДНИЙ!!
	thirdLayer[0] =  "                                   ";
	thirdLayer[1] =  "                                   ";
	thirdLayer[2] =  "                                   ";
	thirdLayer[3] =  "                                   ";
	thirdLayer[4] =  "   IIIIIIIIIIIII                   ";
	thirdLayer[5] =  "   I           I                   ";
	thirdLayer[6] =  "   IB          IIIIIII             ";
	thirdLayer[7] =  "   I                 IIIIIIIIII    ";
	thirdLayer[8] =  " III                B         I    ";
	thirdLayer[9] =  "                             BI    ";
	thirdLayer[10] = "                              I    ";
	thirdLayer[11] = " III       III         B      I    ";
	thirdLayer[12] = " IB        I                  I    ";
	thirdLayer[13] = " IB        I                  I    ";
	thirdLayer[14] = " IIIIIIIIIII                  I    ";
	thirdLayer[15] = "           I                  I    ";
	thirdLayer[16] = "           IIIIIIIIIIIIIIIIIIII    ";
	thirdLayer[17] = "                                   ";
	thirdLayer[18] = "                                   ";
	thirdLayer[19] = "                                   ";

}

void Map::Load()
{
	totalTilesX = tileSheetTexture.getSize().x / tileWidth; // получаем количество плиток по x
	totalTilesY = tileSheetTexture.getSize().y / tileHeight; // по y

	std::cout << totalTilesX << " " << totalTilesY << std::endl;

	try // пытаюсь загрузить текстуру
	{
		tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png");
		sprite.setTexture(tileSheetTexture); // установка спрайта
		std::cout << "Tileset load!" << std::endl;

		if(!tileSheetTexture.loadFromFile("Assets/World/Dungeon/Tileset.png"))
			throw "void::Map::Load()"; // выкидываю ошибку
	}
	catch (const char* errMsg)
	{
		std::cerr << "Problem:" << errMsg << std::endl; // ловлю ошибку
	}

	LayerLoad(firstLayer, firstLayerObjects); // загрузка объектов певрого слоя
	LayerLoad(secondLayer, secondLayerObjects); // загрузка объектов второго слоя
	LayerLoad(thirdLayer, thirdLayerObjects);

}

void Map::LayerLoad(sf::String layer[], std::vector<sf::Sprite>& layerObjects)
{
	for (int i = 0; i < mapHeight; i++) // пробегаюсь по столбцам
		for (int j = 0; j < mapWidth; j++) // а тут по строке
		{
			switch (layer[i][j])
			{
			case('0'): // если 0 рисую случайный пол
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * (rand() % 3), tileHeight * (9 + rand() % 3), tileWidth, tileHeight)); // вот сам пол
				sprite.setScale(sf::Vector2f(5, 5)); // меняю размер с 16 на 16 * Scale.x(.y)
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite); // кидаю плитку в вектор для инфы о ней
				break;
			case('-'): // горизонтальная стена СВЕРХУ
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 3, tileHeight * 0, tileWidth, 2 * tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				//создание хитбокса для спрайта
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('F'): // горизонтальная стена сверху с флагом
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * (3 + rand() % 4), tileHeight * 3, tileWidth, 2 * tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				//создание хитбокса для спрайта
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('_'): // горизонтальная стена СНИЗУ
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 1, tileHeight * 1, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				//создание хитбокса для спрайта
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('|'): // вертикальная стена
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 1, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case(']'): // разворот стены по часовой сверху
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 4, tileHeight * 0, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('['): // разворот стены против часовой сверху
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 0, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('{'): // разворот стены против часовой снизу
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 2, tileWidth, tileHeight * 2));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('<'): // разворот стены против часовой снизу на нижнюю стену
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 2, tileHeight * 2, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('}'): // разворот стены по часовой снизу
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 4, tileHeight * 1, tileWidth, tileHeight * 2));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('>'): // разворот стены по часовой снизу на нижнюю стену
				sprite.setOrigin(0, 0);
				sprite.setTextureRect(sf::IntRect(tileWidth * 4, tileHeight * 1, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('S'): // черепок
				sprite.setOrigin(sf::Vector2f(0, 0));
				sprite.setTextureRect(sf::IntRect(tileWidth * 15, tileHeight * 4, tileWidth, tileHeight));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				layerObjects.push_back(sprite);
				break;
			case('B'): // бочка
				sprite.setOrigin(sf::Vector2f(0, 0));
				sprite.setTextureRect(sf::IntRect(tileWidth * (rand() % 2 + 7), tileHeight * 5 + 7, tileWidth, tileHeight + 4));
				sprite.setScale(sf::Vector2f(4, 4));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				// создание хитбокса для спрайта
				CreateHitbox(sprite, tileWidth * sprite.getScale().x,tileHeight * sprite.getScale().y - 40, 0, 40);
				layerObjects.push_back(sprite);
				break;
			case('D'): // дверь
				sprite.setOrigin(sf::Vector2f(0, tileHeight));
				sprite.setTextureRect(sf::IntRect(tileWidth * 0, tileHeight * 5, tileWidth * 3, tileHeight * 2));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				// создание хитбокса для спрайта
				CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);
				layerObjects.push_back(sprite);
				break;
			case('d'): // развернутая дверь
				sprite.setOrigin(sf::Vector2f(0, 0));
				sprite.setTextureRect(sf::IntRect(tileWidth * 3, tileHeight * 5, tileWidth * 3, tileHeight * 2));
				sprite.setScale(sf::Vector2f(5, 5));
				sprite.setPosition(j * tileWidth * 5, i * tileHeight * 5);
				// создание хитбокса для спрайта
				/*CreateHitbox(sprite, tileWidth * sprite.getScale().x, tileHeight * sprite.getScale().y, 0, 0);*/
				layerObjects.push_back(sprite);
				break;
			case('C'): // мишень
				Combat* combat = new Combat();
				combat->CreateAnimation();
				combat->getSprite()->setPosition(j * tileWidth * 5, i * tileHeight * 5);
				CreateHitbox(*combat->getSprite(), tileWidth * 2, tileHeight * 6, 47, 25);
				animationObjects.push_back(combat);
				break;
			}
		}
}

// метод создания хитбоксов
void Map::CreateHitbox(sf::Sprite &sprite, int x, int y, int posX, int posY)
{
	std::cout << "CreateHitbox Working!" << std::endl;
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2);
	hitbox.setSize(sf::Vector2f(x, y));
	hitbox.setPosition(sprite.getPosition().x + posX, sprite.getPosition().y + posY);
	mapHitbox.push_back(hitbox);
}

void Map::Update(float deltaTime) // взаимодействие игрока и карты
{
	
}

// отрисовка первого слоя карты
void Map::DrawFirstLayer(sf::RenderWindow& window)
{
	for (const auto & tiles : firstLayerObjects)
		window.draw(tiles);

	for (const auto& tiles : secondLayerObjects)
		window.draw(tiles);

	for (size_t i = 0; i < animationObjects.size(); i++)
	{
		sf::Sprite* animSprite = animationObjects[i]->UpdateAnimation();
		window.draw(*animSprite);
	}

	/*for (const auto& hitbox : mapHitbox)
		window.draw(hitbox);*/
}

// отрисовка второго слоя карты
void Map::DrawSecondLayer(sf::RenderWindow& window)
{
	for (const auto& hitbox : thirdLayerObjects)
		window.draw(hitbox);
}
