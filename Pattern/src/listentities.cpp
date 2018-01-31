#include "listentities.h"
#include "bulletspool.h"
#include "dropcoinuntildie.h"
#include "memento.h"
#include "redenemy.h"

ListEntities::ListEntities(Level& level)
{
  med = new HealthMediator();

  chain.add(&attack);
  chain.add(&remove);
  remove.setNext(&chain);

  inspect = std::make_shared<Inspector>();

  level_objects_ = level.GetAllObjects();
  FactoryMethod* factory = new SimpleEnemy();
  FactoryMethod* factory_r = new RedEnemy();
  SimpleFactory sim_factory;
  BigFactory big_factory;

  for (auto el : level_objects_) {
    if (el.name == "playerSpawn") {
      player_ = std::make_shared<Player>(&level, el.rect.left, el.rect.top);
      med->setPlayer(player_.get());
      player_->mediator = med;
    } else if (el.name == "LootBox") {
      auto box = std::make_shared<LootBox>(el.rect);
      loot_boxes_.push_back(box);
    } else if (el.name == "Coin") {
      auto coin = std::make_shared<Coin>(el.rect);
      coins_.push_back(coin);
    } else if (el.name == "Enemy") {
      auto enemy = factory->createObject(
        player_.get(), &level, double(el.rect.left), double(el.rect.top));
      enemys_.push_back(enemy);
    } else if (el.name == "EnemyRed") {
      auto enemy = factory_r->createObject(
        player_.get(), &level, double(el.rect.left), double(el.rect.top));
      enemys_.push_back(enemy);
    } else if (el.name == "FlyEnemy") {
      auto enemy = std::make_shared<FlyEnemy>(
        player_.get(), &level, double(el.rect.left), double(el.rect.top));
      fly_enemys_.push_back(enemy);
    } else if (el.name == "NPC") {
      auto npc = sim_factory.createNPC(&level, double(el.rect.left),
                                       double(el.rect.top));
      npc_.push_back(npc);
      med->setNPC(npc.get());
      npc->mediator = med;
    } else if (el.name == "BigNPC") {
      auto npc = big_factory.createNPC(&level, double(el.rect.left),
                                       double(el.rect.top));
      npc_.push_back(npc);
    }
  }
}

bool
isDie(std::shared_ptr<Entity> bullet)
{
  return !bullet->life_;
}

void
ListEntities::update(const double& time)
{
  player_->handleInput();
  player_->update(time);
  for (auto& el : enemys_) {
    el->update(time);
    if (!el->life_) {
      el->accept(new DropCoinUntilDie());
    }
  }
  for (auto& el : fly_enemys_) {
    el->update(time);
    if (!el->life_) {
      el->accept(new DropCoinUntilDie());
    }
    chain.handle(el, player_);
  }
  for (auto& el : npc_) {
    el->update(time);
    if (inspect->intersect(el, player_) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      player_->Send();
      el->Send();
    }
  }
  for (auto& el : loot_boxes_) {
    el->update(time);
    //    bool touch = inspect->intersect(player_, el);
    bool touch = inspect->intersectWithLoot(player_, el);
    if (touch) {
      //      el->execute(player_);
      loot_boxes_.remove(el);
      break;
    }
  }
  for (auto& el : coins_) {
    el->update(time);
    //    bool touch = inspect->intersect(player_, el);
    bool touch = inspect->intersectWithLoot(player_, el);
    if (touch) {
      //      el->execute(player_);
      coins_.remove(el);
      break;
    }
  }
  for (auto& el : bullets_) {
    el->update(time);
    for (auto& object : level_objects_) {
      if (object.name == "solid" && inspect->intersect(el, object))
        el->life_ = false;
    }
    for (auto& enemy : enemys_) {
      if (inspect->intersect(el, enemy)) {
        enemy->health_ -= el->health_;
        el->life_ = false;
      }
    }
    for (auto& enemy : fly_enemys_) {
      if (inspect->intersect(el, enemy)) {
        enemy->health_ -= el->health_;
        el->life_ = false;
      }
    }
    //    if (el.use_count() > 1)
    //    std::cout << el->position_x_ << std::endl;
    if (isDie(el)) {
      BulletsPool::getInstance()->releaseBullet(el);
      bullets_.remove(el);
      break;
    }
  }
  //  bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(), compFar),
  //                 bullets_.end());
  enemys_.erase(std::remove_if(enemys_.begin(), enemys_.end(), isDie),
                enemys_.end());
  fly_enemys_.erase(
    std::remove_if(fly_enemys_.begin(), fly_enemys_.end(), isDie),
    fly_enemys_.end());
  std::cout << player_->health_ << std::endl;
}

std::shared_ptr<Player>
ListEntities::getPlayer() const
{
  return player_;
}

void
ListEntities::draw(sf::RenderWindow& window)
{
  sf::Sprite sprite = player_->getPicture();
  window.draw(sprite);
  for (const auto& el : enemys_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  for (const auto& el : fly_enemys_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  for (const auto& el : npc_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  for (const auto& el : loot_boxes_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  for (const auto& el : coins_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  for (const auto& el : bullets_) {
    sprite = el->getPicture();
    window.draw(sprite);
  }
  //  std::cout << bullets_.size() << std::endl;
}

void
ListEntities::draw(Bridge& window)
{
  sf::Sprite sprite = player_->getPicture();
  window.draw(sprite, "Player");
  for (const auto& el : loot_boxes_) {
    sprite = el->getPicture();
    window.draw(sprite, "LootBox");
  }
  for (const auto& el : bullets_) {
    sprite = el->getPicture();
    window.draw(sprite, "Bullet");
  }
}

void
ListEntities::push_bullet(std::shared_ptr<Bullet>&& bullet)
{
  bullets_.push_back(bullet);
  //    std::cout << bullets_.size() << std::endl;
}

Memento*
ListEntities::getState()
{
  return new Memento(*this);
}

void
ListEntities::setState(Memento* state)
{
  auto tmp_player_state = player_->state_;
  auto tmp_player_anim = player_->animate_;
  //  player_ = std::make_shared<Player>(*state->returnState()->player_);
  *player_ = *state->returnState()->player_;
  player_->state_ = tmp_player_state;
  player_->animate_ = tmp_player_anim;
  enemys_.clear();
  loot_boxes_.clear();
  coins_.clear();

  for (auto& el : state->returnState()->enemys_) {
    enemys_.push_back(std::make_shared<Enemy>(*el));
  }
  for (auto& el : state->returnState()->loot_boxes_) {
    loot_boxes_.push_back(std::make_shared<LootBox>(*el.get()));
  }
  for (auto& el : state->returnState()->coins_) {
    coins_.push_back(std::make_shared<Coin>(*el.get()));
  }
  notify();
  //  *this = *new ListEntities(*state->returnState());
}

void
ListEntities::notify()
{
  for (auto& el : enemys_) {
    el->setSubject(player_.get());
  }
}
