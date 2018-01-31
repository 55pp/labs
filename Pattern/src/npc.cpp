#include "npc.h"
#include "onlyidle.h"

NPC::NPC(Level* lvl, double&& x, double&& y)
  : Dummy("NPC", lvl, std::move(x), std::move(y), 32, 36)
{
  health_ = 50;
  state_ = new OnlyIdle(*this);
}

void
NPC::update(const double& time)
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
NPC::Send()
{
  mediator->Send(100, this);
}

void
NPC::getPay(int&& pay)
{
  health_restore = pay * 10;
}

NPC::~NPC()
{
}
