#ifndef INSPECTOR_H
#define INSPECTOR_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Entity;
class Object;
class Player;
class Loot;
class Inspector
{
public:
  Inspector();
  bool intersect(std::shared_ptr<Entity>&& a, std::shared_ptr<Entity>&& b);
  bool intersect(std::shared_ptr<Entity>&& a, Object& b);
  bool intersectWithMap(std::shared_ptr<Entity>&& object,
                        std::vector<Object>& map);
  bool intersectWithLoot(std::shared_ptr<Player>& actor,
                         std::shared_ptr<Loot>&& loot);
};

#endif // INSPECTOR_H
