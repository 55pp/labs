#include "blockattack.h"
#include "flyaction.h"
#include "flyenemy.h"
#include "player.h"
#include <cmath>
#include <cstring>

void
BlockAttack::handle(std::shared_ptr<FlyEnemy>& enemy,
                    std::shared_ptr<Player>& actor)
{
  double position_enemy_x = enemy->spawn_x + enemy->width_ / 2;
  double position_enemy_y = enemy->spawn_y + enemy->height_ / 2;
  double position_actor_x = actor->position_x_ + actor->width_ / 2;
  double position_actor_y = actor->position_y_ + actor->height_ / 2;
  double distance = sqrt(pow((position_actor_x - position_enemy_x), 2) +
                         pow((position_actor_y - position_enemy_y), 2));
  std::cout << distance << " Attack" << std::endl;
  if (distance < 200) {
    if (enemy->current_state != FlyEnemy::States::ATTACK) {
      delete enemy->state_;
      enemy->state_ = new FlyAction(*enemy);
      enemy->current_state = FlyEnemy::States::ATTACK;
    }
    //    std::cout << distance << " Attack" << std::endl;
    //    if (strcmp(typeid(enemy->state_).name(), "FlyIdle") == 0) {
    //      delete enemy->state_;
    //      enemy->state_ = new FlyAction(*enemy);
    //    }
    position_enemy_x = enemy->position_x_ + enemy->width_ / 2;
    position_enemy_y = enemy->position_y_ + enemy->height_ / 2;
    enemy->velocity_x_ = (position_actor_x - position_enemy_x) / 1000;
    enemy->velocity_y_ = (position_actor_y - position_enemy_y) / 1000;
    if (enemy->velocity_x_ > 0)
      enemy->sprite_.setScale(-1, 1);
    else
      enemy->sprite_.setScale(1, 1);
    //    std::cout << enemy->velocity_x_ << " " << enemy->velocity_y_ <<
    //    std::endl;
  } else {
    Chain::handle(enemy, actor);
    //    next_->handle(enemy, actor);
  }
}
