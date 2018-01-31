#include "enemy.h"
#include "onlyidle.h"
#include "operation.h"
#include "player.h"

Enemy::Enemy(Player* gamer, Level* lvl, double&& x, double&& y)
  : Dummy("Enemy", lvl, std::move(x), std::move(y), 32, 36)
{
  gamer_ = gamer;
  state_ = new OnlyIdle(*this);
  health_ = 100;
}

Enemy::Enemy(std::string name, Player* gamer, Level* lvl, double&& x,
             double&& y)
  : Dummy(std::move(name), lvl, std::move(x), std::move(y), 32, 36)
{
  gamer_ = gamer;
  state_ = new OnlyIdle(*this);
  health_ = 100;
}

void
Enemy::update(const double& time)
{
  state_->update(*this, time);
  sprite_.setPosition(float(position_x_ + width_ / 2),
                      float(position_y_ + height_ / 2));
  if (health_ <= 0) {
    life_ = false;
  }

  if (position_y_ >= 768 - height_) {
    velocity_y_ = 0;
    position_y_ = 768 - height_;
  }
  frame_ += 0.005 * time;
  if (frame_ > 1) {
    animate_->action(texture_, sprite_);
    frame_ = 0;
  }
}

void
Enemy::setSubject(Player* gamer)
{
  //  delete gamer_;
  gamer_ = gamer;
}

void
Enemy::accept(Operation* o)
{
  o->visit(this);
}

Enemy::~Enemy()
{
  if (!life_)
    gamer_->experience_ += experience_;
}
