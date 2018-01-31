#include "jumpstate.h"
#include "fallstate.h"

State*
JumpState::handleInput(Dummy& actor)
{
  actor.speed_ = 0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    actor.sprite_.setScale(-1, 1);
    actor.speed_ = -0.1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    actor.sprite_.setScale(1, 1);
    actor.speed_ = 0.1;
  }
  if (actor.velocity_y_ > 0) {
    return new FallState(actor);
    //    return std::make_shared<FallState>(actor);
  }
  return nullptr;
}

void
JumpState::update(Dummy& actor, const double& time)
{
  actor.velocity_y_ = actor.velocity_y_ + 0.0015 * time;
  actor.position_y_ += actor.velocity_y_ * time;
  actor.velocity_x_ = actor.speed_;
  actor.position_x_ += actor.velocity_x_ * time;
  //  std::cout << actor.velocity_y << std::endl;
  for (auto& object : actor.objects_) {
    if (actor.getRect().intersects(object.rect) && object.name == "solid") {
      int pos_x = int(actor.position_x_);
      int pos_y = int(actor.position_y_);
      int obj_x = int(object.rect.left);
      int obj_y = int(object.rect.top);
      int obj_w = int(object.rect.width);
      int obj_h = int(object.rect.height);
      if ((obj_x < pos_x && (pos_x + actor.width_) < (obj_x + obj_w)) &&
          (pos_y <= (obj_y + obj_h))) {
        actor.position_y_ =
          double(object.rect.top) + double(object.rect.height);
        actor.velocity_y_ = 0;
      } else if (actor.velocity_x_ > 0 &&
                 (pos_y > obj_y && pos_y < (obj_y + obj_h))) {
        actor.position_x_ = double(object.rect.left) - actor.width_;
      } else if (actor.velocity_x_ < 0 &&
                 (pos_y > obj_y && pos_y < obj_y + obj_h)) {
        actor.position_x_ =
          double(object.rect.left) + double(object.rect.width);
      }
    }
  }
}
JumpState::JumpState(Dummy& actor)
{
  actor.velocity_y_ = -jump_strength;
  //  delete actor.animate_;
  //  actor.animate_ = new PlayerJump();
  path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                  "Sprites/player/player-jump.png";
  actor.animate_ = std::make_shared<IAnimation>(path_to_image, 4, 0, 2, false);
}
