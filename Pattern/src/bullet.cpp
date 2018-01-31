#include "bullet.h"
#include "simplefly.h"
#include "zigzagfly.h"

std::unique_ptr<BulletModel> Bullet::model_ = NULL;

Bullet::Bullet(Level* lvl, double x, double y, int&& dir)
  : Dummy("Bullet", lvl, std::move(x), std::move(y), 21, 11)
{
  //  str_fly = new SimpleFly(this);
  str_fly = new ZigZagFly(this);
  direction_ = dir % 2;
  speed_ = 0.1;
  health_ = 10;
  //  animate_ = new BulletMove();
  //  std::string path_to_image =
  //    "/home/konstantin/QtProjects/Pattern/src/Resource/"
  //    "Sprites/misc/shoot.png";
  //  animate_ = std::make_shared<IAnimation>(path_to_image, 3);
  if (Bullet::model_ == nullptr) {
    Bullet::model_ = std::make_unique<BulletModel>();
  }
  sprite_.setScale(dir, 1);
}

Bullet::~Bullet()
{
  //  delete str_fly;
  //  delete animate_;
}

void
Bullet::update(const double& time)
{
  str_fly->doIt(this);
  position_x_ += velocity_x_ * time;
  position_y_ += velocity_y_ * time;
  sprite_.setPosition(float(position_x_ + width_ / 2),
                      float(position_y_ + height_ / 2));
  if (health_ <= 0) {
    life_ = false;
  }

  frame_ += 0.01 * time;
  if (frame_ > 1) {
    // animate_->action(texture_, sprite_);
    model_->update(texture_, sprite_, current_frame_);
    sprite_.setScale(direction_, 1);
    frame_ = 0;
  }
}

std::shared_ptr<Bullet>
Bullet::clone(Level* lvl, double x, double y, int&& dir)
{
  (void)lvl;
  (void)x;
  (void)y;
  (void)dir;
  //  return std::make_shared<Bullet>(lvl, x, y, std::move(dir));
  return std::make_shared<Bullet>(*this);
}
