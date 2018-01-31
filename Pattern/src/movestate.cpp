#include "movestate.h"
#include "fallstate.h"
#include "idlestate.h"
#include "jumpstate.h"

State*
MoveState::handleInput(Dummy& actor)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    actor.sprite_.setScale(-1, 1);
    actor.speed_ = -0.1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    actor.sprite_.setScale(1, 1);
    actor.speed_ = 0.1;
  } else {
    //    return std::make_shared<IdleState>(actor);
    return new IdleState(actor);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    //    return std::make_shared<JumpState>(actor);
    return new JumpState(actor);
  }
  if (actor.velocity_y_ > 0) {
    //    return std::make_shared<FallState>(actor);
    return new FallState(actor);
  }
  return nullptr;
}
void
MoveState::update(Dummy& actor, const double& time)
{
  actor.velocity_y_ = actor.velocity_y_ + 0.0015 * time;
  actor.position_y_ += actor.velocity_y_ * time;
  actor.velocity_x_ = actor.speed_;
  actor.position_x_ += actor.velocity_x_ * time;

  for (auto& object : actor.objects_) {
    if (actor.getRect().intersects(object.rect) && object.name == "solid") {
      if (actor.velocity_y_ >= 0 &&
          (actor.position_y_ < double(object.rect.top))) {
        actor.position_y_ = double(object.rect.top) - actor.height_;
        actor.velocity_y_ = 0;
      }
      if (actor.velocity_x_ > 0 &&
          (actor.position_y_ > double(object.rect.top))) {
        actor.position_x_ = double(object.rect.left) - actor.width_;
      }
      if (actor.velocity_x_ < 0 &&
          (actor.position_y_ > double(object.rect.top))) {
        actor.position_x_ =
          double(object.rect.left) + double(object.rect.width);
      }
    }
  }
  //    std::cout << "move" << std::endl;
}
MoveState::MoveState(Dummy& actor)
{
  //  delete actor.animate_;
  //  actor.animate_ = new PlayerMove();
  path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                  "Sprites/player/player-run.png";
  actor.animate_ = std::make_shared<IAnimation>(path_to_image, 8);
}
