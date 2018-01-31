#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <memory>

class Enemy;
class NPC;
class Level;
class Player;
class AbstractFactory
{
public:
  AbstractFactory();
  virtual std::shared_ptr<Enemy> createEnemy(Player* gamer, Level* lvl,
                                             double&& x, double&& y) = 0;
  virtual std::shared_ptr<NPC> createNPC(Level* lvl, double&& x,
                                         double&& y) = 0;
};

#endif // ABSTRACTFACTORY_H
