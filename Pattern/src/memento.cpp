#include "memento.h"
#include "listentities.h"

Memento::Memento(ListEntities& list)
{
  ListEntities tmp_list;
  tmp_list.player_ = std::make_shared<Player>(*list.player_.get());
  for (auto& el : list.enemys_) {
    tmp_list.enemys_.push_back(std::make_shared<Enemy>(*el.get()));
  }
  for (auto& el : list.loot_boxes_) {
    tmp_list.loot_boxes_.push_back(std::make_shared<LootBox>(*el.get()));
  }
  for (auto& el : list.coins_) {
    tmp_list.coins_.push_back(std::make_shared<Coin>(*el.get()));
  }
  for (auto& el : list.bullets_) {
    tmp_list.bullets_.push_back(std::make_shared<Bullet>(*el.get()));
  }

  reserv_ = std::make_shared<ListEntities>(tmp_list);
}

std::shared_ptr<ListEntities>
Memento::returnState()
{
  return reserv_;
}
