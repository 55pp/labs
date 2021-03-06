#include "flyidle.h"

FlyIdle::FlyIdle(Dummy& actor)
{
  path_to_image = "/home/konstantin/QtProjects/Pattern/src/Resource/"
                  "Sprites/enemy/skull-perched.png";
  actor.animate_ = std::make_shared<IAnimation>(path_to_image, 4);
}

State*
FlyIdle::handleInput(Dummy& actor)
{
  (void)actor;
  return nullptr;
}

void
FlyIdle::update(Dummy& actor, const double& time)
{
  actor.position_x_ += actor.velocity_x_ * time;
  actor.position_y_ += actor.velocity_y_ * time;
}
