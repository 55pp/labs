#include "blockidle.h"
#include "flyaction.h"
#include "flyenemy.h"
#include "flyidle.h"
#include "player.h"
#include <cmath>
#include <cstring>

void
BlockIdle::handle(std::shared_ptr<FlyEnemy>& enemy,
                  std::shared_ptr<Player>& actor)
{
  double position_enemy_x = enemy->position_x_ + enemy->width_ / 2;
  double position_enemy_y = enemy->position_y_ + enemy->height_ / 2;
  double position_actor_x = actor->position_x_ + actor->width_ / 2;
  double position_actor_y = actor->position_y_ + actor->height_ / 2;
  double distance = sqrt(pow((position_actor_x - position_enemy_x), 2) +
                         pow((position_actor_y - position_enemy_y), 2));
  enemy->velocity_x_ = enemy->velocity_y_ = 0;
  //  std::cout << distance << " Idle" << std::endl;
  if (distance > 200) {
    if (enemy->current_state != FlyEnemy::States::IDLE) {
      delete enemy->state_;
      enemy->state_ = new FlyIdle(*enemy);
      enemy->current_state = FlyEnemy::States::IDLE;
    }

    //    if (strcmp(typeid(enemy->state_).name(), "FlyAction") == 0) {
    //    delete enemy->state_;
    //    enemy->state_ = new FlyAction(*enemy);
    //    }

  } else {
    //    next_->handle(enemy, actor);
    Chain::handle(enemy, actor);
  }
}
