#ifndef LISTENTITIES_H
#define LISTENTITIES_H
#include "bigfactory.h"
#include "blockattack.h"
#include "blockidle.h"
#include "blockremove.h"
#include "bridge.h"
#include "bullet.h"
#include "coin.h"
#include "enemy.h"
#include "flyenemy.h"
#include "healthmediator.h"
#include "inspector.h"
#include "level.h"
#include "lootbox.h"
#include "npc.h"
#include "player.h"
#include "simpleenemy.h"
#include "simplefactory.h"

class Memento;
class ListEntities
{
public:
  ListEntities() {}
  ListEntities(Level& level);
  void update(const double& time);
  std::shared_ptr<Player> getPlayer() const;
  void draw(sf::RenderWindow& window);
  void draw(Bridge& window);
  void push_bullet(std::shared_ptr<Bullet>&& bullet);
  Memento* getState();
  void setState(Memento* state);
  void notify();

private:
  friend class Memento;
  friend class DropCoinUntilDie;
  std::shared_ptr<Player> player_;
  std::list<std::shared_ptr<Enemy>> enemys_;
  std::list<std::shared_ptr<FlyEnemy>> fly_enemys_;
  std::list<std::shared_ptr<NPC>> npc_;
  std::list<std::shared_ptr<LootBox>> loot_boxes_;
  std::list<std::shared_ptr<Coin>> coins_;
  std::list<std::shared_ptr<Bullet>> bullets_;
  std::shared_ptr<Inspector> inspect;
  std::vector<Object> level_objects_;
  BlockIdle chain;
  BlockAttack attack;
  BlockRemove remove;
  HealthMediator* med;
};

#endif // LISTENTITIES_H
