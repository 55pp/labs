#include "fallstate.h"
#include "idlestate.h"

State*
FallState::handleInput(Dummy& actor)
{
  actor.speed_ = 0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    actor.sprite_.setScale(-1, 1);
    actor.speed_ = -0.1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    actor.sprite_.setScale(1, 1);
    actor.speed_ = 0.1;
  }
  if (actor.velocity_y_ == 0) {
    //    return std::make_shared<IdleState>(actor);
    return new IdleState(actor);
  }
  return nullptr;
}
void
FallState::update(Dummy& actor, const double& time)
{
  actor.velocity_y_ = actor.velocity_y_ + 0.0015 * time;
  actor.position_y_ += actor.velocity_y_ * time;
  actor.velocity_x_ = actor.speed_;
  actor.position_x_ += actor.velocity_x_ * time;
  //  std::cout << "fall" << std::endl;
  for (auto& object : actor.objects_) {
    if (actor.getRect().intersects(object.rect) && object.name == "solid") {
      if (actor.velocity_y_ >= 0 && (actor.position_y_ < object.rect.top)) {
        actor.position_y_ = object.rect.top - actor.height_;
        actor.velocity_y_ = 0;
      }
      if (actor.velocity_x_ > 0 && (actor.position_y_ > object.rect.top)) {
        actor.position_x_ = object.rect.left - actor.width_;
      }
      if (actor.velocity_x_ < 0 && (actor.position_y_ > object.rect.top)) {
        actor.position_x_ = object.rect.left + object.rect.width;
      }
    }
  }
}
FallState::FallState(Dummy& actor)
{
  //  delete actor.animate_;
  //  actor.animate_ = new PlayerFall();
  path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                  "Sprites/player/player-jump.png";
  actor.animate_ = std::make_shared<IAnimation>(path_to_image, 4, 2, 4, false);
}
