#ifndef RENDERCONSOLE_H
#define RENDERCONSOLE_H
#include "bridge.h"
#include <chrono>
#include <time.h>
#include <vector>

class Entity;
class RenderConsole : public Bridge
{
public:
  RenderConsole(const size_t& width, const size_t& height);
  void draw(sf::Sprite& sprite, std::string&& name_object);
  void display();
  void clear();
  ~RenderConsole() {}
private:
  std::vector<std::vector<char>> tiles_;
  std::chrono::milliseconds s_time_;
  std::chrono::milliseconds msec_;
};

#endif // RENDERCONSOLE_H
