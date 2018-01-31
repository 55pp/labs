#ifndef LOOTBOX_H
#define LOOTBOX_H
#include "loot.h"
#include "lootboxidle.h"
#include <list>

class LootBox : public Loot
{
public:
  LootBox(double x, double y, int w, int h);
  LootBox(sf::FloatRect rect);
  void execute(std::shared_ptr<Player>& actor);
  void add(const std::shared_ptr<Loot>& loot);
  void remove(const std::shared_ptr<Loot>& loot);
  ~LootBox();

private:
  std::list<std::shared_ptr<Loot>> children_;
};

#endif // LOOTBOX_H
