#include "bigenemy.h"

BigEnemy::BigEnemy(Player* gamer, Level* lvl, double&& x, double&& y)
  : Enemy(gamer, lvl, std::move(x), std::move(y))
{
  health_ = 500;
  sprite_.setScale(4, 4);
  sprite_.setColor(sf::Color(255, 0, 0));
  width_ *= 4;
  height_ *= 4;
}

BigEnemy::~BigEnemy()
{
}
