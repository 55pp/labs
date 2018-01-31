#include "player.h"
#include "bulletconstructor.h"
#include "firebullet.h"
#include "idlestate.h"
#include "onlyidle.h"

Player::Player(Level* lvl, double&& x, double&& y)
  : Dummy("Player", lvl, std::move(x), std::move(y), 32, 36)
{
  state_ = new IdleState(*this);
  auto simple_bullet = std::make_shared<Bullet>(lvl, position_x_, position_y_,
                                                sprite_.getScale().x);
  gun_ = std::make_shared<Gun>(simple_bullet);
}

Player::~Player()
{
  //  delete state_;
  //  delete animate;
}

void
Player::update(const double& time)
{
  //    state_.get()->update(*this, time);
  state_->update(*this, time);
  sprite_.setPosition(position_x_ + width_ / 2, position_y_ + height_ / 2);
  if (health_ <= 0) {
    life_ = false;
  }

  if (experience_ >= level_cap_) {
    ++level_;
    experience_ -= level_cap_;
    level_cap_ *= 1.1;
  }

  if (position_y_ >= 768 - height_) {
    velocity_y_ = 0;
    position_y_ = 768 - height_;
  }
  frame_ += 0.01 * time;
  if (frame_ > 1) {
    animate_->action(texture_, sprite_);
    frame_ = 0;
  }
}

void
Player::handleInput()
{
  auto new_state = state_->handleInput(*this);
  //  std::cout << new_state << std::endl;
  if (new_state != nullptr) {
    delete state_;
    state_ = std::move(new_state);
  }
}

void
Player::Send()
{
  mediator->Send(int(health_), this);
}

void
Player::getHeal(int&& heal)
{
  health_ += heal;
}

std::shared_ptr<Bullet>
Player::shoot()
{
  BulletConstructor constr;
  FireBullet fire_build(lvl_, position_x_, position_y_, sprite_.getScale().x);
  auto fire_bullet = constr.makeBullet(fire_build);
  gun_->setPrototype(fire_bullet);
  return gun_->shoot(lvl_, position_x_, position_y_, sprite_.getScale().x);
}
