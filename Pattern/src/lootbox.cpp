#include "lootbox.h"
#include "coin.h"

LootBox::LootBox(double x, double y, int w, int h)
  : Loot("LootBox", std::move(x), std::move(y), std::move(w), std::move(h))
{
  //  animate_ = new LootBoxIdle();
  std::string path_to_image =
    "/home/konstantin/QtProjects/Pattern/src/Resource/"
    "Sprites/misc/health.png";
  animate_ = std::make_shared<IAnimation>(path_to_image, 4);
  for (int i = 0; i < 10; ++i) {
    children_.push_back(std::make_shared<Coin>(0, 0, 16, 16));
  }
}

LootBox::LootBox(sf::FloatRect rect)
  : Loot("LootBox", rect)
{
  //  animate_ = new LootBoxIdle();
  std::string path_to_image =
    "/home/konstantin/QtProjects/Pattern/src/Resource/"
    "Sprites/misc/health.png";
  animate_ = std::make_shared<IAnimation>(path_to_image, 4);
  for (int i = 0; i < 10; ++i) {
    children_.push_back(std::make_shared<Coin>(0, 0, 16, 16));
  }
}

void
LootBox::execute(std::shared_ptr<Player>& actor)
{
  for (auto& el : children_) {
    el->execute(actor);
  }
  children_.clear();
}

void
LootBox::add(const std::shared_ptr<Loot>& loot)
{
  children_.push_back(loot);
}

void
LootBox::remove(const std::shared_ptr<Loot>& loot)
{
  children_.remove(loot);
}

LootBox::~LootBox()
{
  //  delete animate_;
}
