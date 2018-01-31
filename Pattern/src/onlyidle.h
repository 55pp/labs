#ifndef ONLYIDLE_H
#define ONLYIDLE_H
#include "dummy.h"
#include "enemyidle.h"
#include "ianimation.h"
#include "playeridle.h"
#include "state.h"

class OnlyIdle : public State
{
public:
  ~OnlyIdle() {}
  virtual State* handleInput(Dummy& actor)
  {
    std::ignore = actor;
    return nullptr;
  }
  virtual void update(Dummy& actor, const double& time)
  {
    actor.velocity_y_ = actor.velocity_y_ + 0.0015 * time;
    actor.position_y_ += actor.velocity_y_ * time;
    for (auto& object : actor.objects_) {
      if (actor.getRect().intersects(object.rect) && object.name == "solid") {
        actor.position_y_ = double(object.rect.top) - actor.height_;
        actor.velocity_y_ = 0;
      }
    }
  }
  explicit OnlyIdle(Dummy& actor)
  {
    if (actor.name_ == "Enemy")
      actor.animate_ = std::make_shared<IAnimation>(path_to_image_, 2);
    else
      actor.animate_ = std::make_shared<IAnimation>(path_to_image_NPC_, 3);
  }

private:
  std::string path_to_image_ = "/home/konstantin/QtProjects/Pattern/src/"
                               "Resource/Sprites/enemy/frog-idle.png";
  //  std::string path_to_image_ = "/home/konstantin/QtProjects/Pattern/src/"
  //                               "Resource/Sprites/enemy/rotate.png";
  std::string path_to_image_NPC_ = "/home/konstantin/QtProjects/Pattern/src/"
                                   "Resource/Sprites/npc/npc-male-idle.png";
};

#endif // ONLYIDLE_H
