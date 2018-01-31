#include "shootstate.h"
#include "bulletspool.h"
#include "idlestate.h"

ListEntities* ShootState::visor_ = NULL;

State*
ShootState::handleInput(Dummy& actor)
{
  // std::cout << delay << std::endl;
  if (delay_ <= 0) {
    return new IdleState(actor);
  }
  delay_--;
  return nullptr;
}
void
ShootState::update(Dummy& actor, const double& time)
{
  actor.position_y_ += actor.velocity_y_ * time;
  //    actor->velocity_x = actor->speed;
  //    actor->position_x += actor->velocity_x * time;
}
ShootState::ShootState(Dummy& actor)
{
  //  delete actor.animate_;
  //  actor.animate_ = new PlayerShoot();
  // actor->delay = 1;
  visor_->push_bullet(actor.shoot());
  //  visor_->push_bullet(BulletsPool::getInstance()->getBullet(
  //    actor.position_x_, actor.position_y_, actor.sprite_.getScale().x));
  path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                  "Sprites/player/player-shoot.png";
  actor.animate_ = std::make_shared<IAnimation>(path_to_image, 2);
}

void
ShootState::setVisor(ListEntities* visor)
{
  ShootState::visor_ = visor;
}
