#include "flyenemy.h"
#include "flyidle.h"

FlyEnemy::FlyEnemy(Player* gamer, Level* lvl, double&& x, double&& y)
  : Enemy("FlyEnemy", gamer, lvl, std::move(x), std::move(y))
{
  health_ = 10;
  state_ = new FlyIdle(*this);
  current_state = States::IDLE;
  spawn_x = x;
  spawn_y = y;
  speed_ = 0.1;
}

void
FlyEnemy::update(const double& time)
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

FlyEnemy::~FlyEnemy()
{
}
