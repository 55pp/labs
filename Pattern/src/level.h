#ifndef LEVEL_H
#define LEVEL_H
#include "renderconsole.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Object
{
  int GetPropertyInt(std::string name); //номер свойства объекта в нашем списке
  float GetPropertyFloat(std::string name);
  std::string GetPropertyString(std::string name);

  std::string name = "unknow"; //объявили переменную name типа string
  std::string type; //а здесь переменную type типа string
  sf::Rect<float> rect; //тип Rect с нецелыми значениями
  std::map<std::string, std::string> properties; //создаём ассоциатиный массив.
  //ключ - строковый тип,
  //значение - строковый

  sf::Sprite sprite; //объявили спрайт
};

struct Layer //слои
{
  int opacity;                   //непрозрачность слоя
  std::vector<sf::Sprite> tiles; //закидываем в вектор тайлы
};

class Level
{
public:
  Level();
  Level(const std::string& file_name);
  Object GetObject(std::string name);
  std::vector<Object> GetObjects(
    std::string name); //выдаем объект в наш уровень
  std::vector<Object> GetAllObjects(); //выдаем все объекты в наш уровень
  void Draw(sf::RenderWindow& window); //рисуем в окно
  void Draw(RenderConsole& window);    //рисуем в окно
  sf::Vector2i GetTileSize(); //получаем размер тайла

private:
  std::vector<std::string> getAttributes(std::string& element);
  std::map<std::string, std::string> getMapAttributes(
    std::vector<std::string>& vector_attributes);
  void readTileset(std::ifstream& stream, std::string& str);
  std::string getFilePath(const std::string& source);
  void readObjects(std::ifstream& stream, std::string& str);

  size_t width;
  size_t height;
  size_t tileWidth;
  size_t tileHeight;  //в tmx файле width height в начале,затем размер тайла
  size_t firstTileID; //получаем айди первого тайла
  sf::Rect<float> drawingBounds; //размер части карты которую рисуем
  sf::Texture tilesetImage; //текстура карты
  std::vector<Object> objects; //массив типа Объекты, который мы создали
  std::vector<Layer> layers;
};

#endif // LEVEL_H
