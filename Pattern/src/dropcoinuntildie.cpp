#include "dropcoinuntildie.h"
#include "enemy.h"
#include "listentities.h"

ListEntities* DropCoinUntilDie::visor_ = NULL;

void
DropCoinUntilDie::visit(Enemy* target)
{
  auto coin = std::make_shared<Coin>(target->position_x_,
                                     target->position_y_ - 20, 59, 45);
  visor_->coins_.push_back(coin);
}

void
DropCoinUntilDie::setVisor(ListEntities* visor)
{
  visor_ = visor;
}
