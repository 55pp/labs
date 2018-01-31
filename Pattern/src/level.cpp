#include "level.h"

Level::Level()
{
}

Level::Level(const std::string& file_name)
{
  std::ifstream in(file_name);
  std::string file_string;
  std::getline(in, file_string);
  std::getline(in, file_string);
  file_string = file_string.erase(0, 5);
  file_string = file_string.erase(file_string.size() - 1, 1);
  auto attribute = getAttributes(file_string);
  auto map_attributes = getMapAttributes(attribute);
  std::istringstream(map_attributes["width"]) >> width;
  std::istringstream(map_attributes["height"]) >> height;
  std::istringstream(map_attributes["tilewidth"]) >> tileWidth;
  std::istringstream(map_attributes["tileheight"]) >> tileHeight;
  std::getline(in, file_string);
  while (file_string != "</map>") {
    if (file_string.find("<tileset") != std::string::npos) {
      readTileset(in, file_string);
    } else if (file_string.find("<objectgroup") != std::string::npos) {
      //      std::cout << "kek" << std::endl;
      readObjects(in, file_string);
    }
    std::getline(in, file_string);
  }
  in.close();
}

Object
Level::GetObject(std::string name)
{
  // только первый объект с заданным именем
  for (size_t i = 0; i < objects.size(); i++)
    if (objects[i].name == name)
      return objects[i];
  return Object();
}

std::vector<Object>
Level::GetObjects(std::string name)
{
  // все объекты с заданным именем
  std::vector<Object> vec;
  for (size_t i = 0; i < objects.size(); i++)
    if (objects[i].name == name)
      vec.push_back(objects[i]);

  return vec;
}

std::vector<Object>
Level::GetAllObjects()
{
  return objects;
}

void
Level::Draw(sf::RenderWindow& window)
{
  // рисуем все тайлы (объекты не рисуем!)
  for (size_t layer = 0; layer < layers.size(); layer++)
    for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++) {
      sf::Sprite spr = layers[layer].tiles[tile];
      window.draw(spr);
    }
}

void
Level::Draw(RenderConsole& window)
{
  for (size_t layer = 0; layer < layers.size(); layer++)
    for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++) {
      sf::Sprite spr = layers[layer].tiles[tile];
      window.draw(spr, "solid");
    }
}

sf::Vector2i
Level::GetTileSize()
{
  return sf::Vector2i(int(tileWidth), int(tileHeight));
}

std::vector<std::string>
Level::getAttributes(std::string& element)
{
  std::vector<std::string> attribute;
  size_t pos = 0;
  std::string token;
  while ((pos = element.find(" ")) != std::string::npos) {
    token = element.substr(0, pos);
    //    std::cout << token << std::endl;
    attribute.push_back(token);
    element.erase(0, pos + 1);
  }
  //  std::cout << element << std::endl;
  attribute.push_back(element);
  return attribute;
}

std::map<std::string, std::string>
Level::getMapAttributes(std::vector<std::string>& vector_attributes)
{
  std::map<std::string, std::string> attributes;
  for (auto el : vector_attributes) {
    size_t pos;
    if ((pos = el.find("=")) != std::string::npos) {
      std::string token = el.substr(0, pos);
      el = el.erase(0, pos + 2);
      el = el.erase(el.size() - 1, 1);
      attributes[token] = el;
    }
  }
  return attributes;
}

void
Level::readTileset(std::ifstream& stream, std::string& str)
{
  size_t pathStart = str.find("firstgid=\"") + 10;
  size_t pathEnd = str.find("\"", pathStart);
  std::istringstream(str.substr(pathStart, pathEnd - pathStart)) >> firstTileID;

  pathStart = str.find("source=\"") + 8;
  pathEnd = str.size() - 3;
  std::string source = str.substr(pathStart, pathEnd - pathStart);
  std::string imagePath = getFilePath(source);

  //  sf::Image tileset;

  //  if (!tileset.loadFromFile(imagePath)) {
  //    std::cerr << "File " << imagePath << " not load." << std::endl;
  //  }

  //  tileset.createMaskFromColor(sf::Color(255, 255, 255));
  //  tilesetImage.loadFromImage(tileset);
  tilesetImage.loadFromFile(imagePath);
  tilesetImage.setSmooth(false);

  size_t columns = tilesetImage.getSize().x / tileWidth;
  size_t rows = tilesetImage.getSize().y / tileHeight;

  std::vector<sf::Rect<int>> subRects;

  for (size_t y = 0; y < rows; ++y)
    for (size_t x = 0; x < columns; ++x) {
      sf::Rect<int> rect;

      rect.top = int(y * tileHeight);
      rect.height = int(tileHeight);
      rect.left = int(x * tileWidth);
      rect.width = int(tileWidth);

      subRects.push_back(rect);
    }

  Layer layer;
  layer.opacity = 255;

  std::getline(stream, str);
  std::getline(stream, str);

  for (size_t tileRows = 0; tileRows < width; ++tileRows) {
    std::string rowTiles;
    std::getline(stream, rowTiles);
    std::istringstream sstring(rowTiles);
    for (size_t tileColumns = 0; tileColumns < height; ++tileColumns) {
      int tile;
      char comma;
      sstring >> tile;
      tile -= firstTileID;
      if (tile >= 0) {
        sf::Sprite sprite;
        sprite.setTexture(tilesetImage);
        sprite.setTextureRect(subRects[size_t(tile)]);
        sprite.setPosition(tileColumns * tileWidth, tileRows * tileHeight);
        sprite.setColor(sf::Color(255, 255, 255, uint8_t(layer.opacity)));

        layer.tiles.push_back(sprite); //закидываем в слой спрайты тайлов
      }
      sstring >> comma;
    }
  }

  layers.push_back(layer);
}

std::string
Level::getFilePath(const std::string& source)
{
  std::ifstream in(source);
  if (!in.is_open()) {
    std::cerr << "File " << source << " is not open." << std::endl;
  }
  std::string file_string;
  std::getline(in, file_string);
  std::getline(in, file_string);
  std::getline(in, file_string);
  size_t pathStart = file_string.find("\"") + 1;
  size_t pathEnd = file_string.find("\"", pathStart);
  file_string = file_string.substr(pathStart, pathEnd - pathStart);
  //  std::cout << file_string << std::endl;
  in.close();
  return file_string;
}

void
Level::readObjects(std::ifstream& stream, std::string& str)
{
  std::getline(stream, str);
  while (str.find("<object") != std::string::npos) {
    auto attribute = getAttributes(str);
    auto map_attributes = getMapAttributes(attribute);
    std::string nameObject;
    int x;
    int y;
    int width;
    int height;
    std::istringstream(map_attributes["name"]) >> nameObject;
    std::istringstream(map_attributes["x"]) >> x;
    std::istringstream(map_attributes["y"]) >> y;
    std::istringstream(map_attributes["width"]) >> width;
    std::istringstream(map_attributes["height"]) >> height;

    sf::Sprite sprite;
    sprite.setTexture(tilesetImage);
    sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
    sprite.setPosition(x, y);

    // экземпляр объекта
    Object object;
    object.name = nameObject;
    object.sprite = sprite;

    sf::Rect<float> objectRect;
    objectRect.top = y;
    objectRect.left = x;
    objectRect.height = height;
    objectRect.width = width;
    object.rect = objectRect;

    std::getline(stream, str);

    if (str.find("properties") != std::string::npos) {
      std::getline(stream, str);
      while (str.find("property") != std::string::npos) {
        auto attribute = getAttributes(str);
        auto map_attributes = getMapAttributes(attribute);
        std::string nameProp;
        std::string valueProp;
        std::istringstream(map_attributes["name"]) >> nameProp;
        std::istringstream(map_attributes["value"]) >> valueProp;
        object.properties[nameProp] = valueProp;
      }

      std::getline(stream, str);
      std::getline(stream, str);
      std::getline(stream, str);
    }
    objects.push_back(object);
  }
}

int
Object::GetPropertyInt(std::string name)
{
  return atoi(properties[name].c_str());
}

float
Object::GetPropertyFloat(std::string name)
{
  return strtof(properties[name].c_str(), NULL);
}

std::string
Object::GetPropertyString(std::string name)
{
  return properties[name];
}
