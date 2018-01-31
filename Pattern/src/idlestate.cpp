#include "idlestate.h"
#include "fallstate.h"
#include "jumpstate.h"
#include "movestate.h"
#include "shootstate.h"

State*
IdleState::handleInput(Dummy& actor)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    //    return std::make_shared<MoveState>(actor);
    return new MoveState(actor);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    //    return std::make_shared<MoveState>(actor);
    return new MoveState(actor);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    //    return std::make_shared<JumpState>(actor);
    return new JumpState(actor);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    //    return std::make_shared<ShootState>(actor);
    return new ShootState(actor);
  } else if (actor.velocity_y_ > 0) {
    //    return std::make_shared<FallState>(actor);
    return new FallState(actor);
  }
  return nullptr;
}
void
IdleState::update(Dummy& actor, const double& time)
{
  actor.velocity_y_ = actor.velocity_y_ + 0.0015 * time;
  actor.position_y_ += actor.velocity_y_ * time;
  //  std::cout << "idle" << std::endl;
  for (auto& object : actor.objects_) {
    if (actor.getRect().intersects(object.rect) && object.name == "solid") {
      actor.position_y_ = double(object.rect.top) - actor.height_;
      actor.velocity_y_ = 0;
    }
  }
}
IdleState::IdleState(Dummy& actor)
{
  if (actor.name_ == "Player") {
    //    delete actor.animate_;
    //    actor.animate_ = new PlayerIdle();
    path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                    "Sprites/player/player-idle.png";
    actor.animate_ = std::make_shared<IAnimation>(path_to_image, 4);
  } else if (actor.name_ == "Player2") {
    //    delete actor.animate_;
    //    actor.animate_ = new EnemyIdle();
    path_to_image = "/home/konstantin/QtProjects/Pattern/src/"
                    "Resource/Sprites/enemy/frog-idle.png";
    actor.animate_ = std::make_shared<IAnimation>(path_to_image, 2);
  }
}
