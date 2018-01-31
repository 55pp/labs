#ifndef LOOT_H
#define LOOT_H
#include "entity.h"
//#include "player.h"

class Player;
class Loot : public Entity
{
public:
  explicit Loot(std::string&& _name, double&& x, double&& y, int&& w, int&& h);

  explicit Loot(std::string&& _name, sf::FloatRect rect);

  void update(const double& time);

  virtual void execute(std::shared_ptr<Player>&) = 0;

  virtual void add(const std::shared_ptr<Loot>&) {}

  virtual void remove(const std::shared_ptr<Loot>&) {}
};

#endif // LOOT_H
