#ifndef COIN_H
#define COIN_H
#include "loot.h"
#include "lootboxidle.h"

class Coin : public Loot
{
public:
  Coin(double x, double y, int w, int h);
  Coin(sf::FloatRect rect);
  void execute(std::shared_ptr<Player>& actor);
};

#endif // COIN_H
