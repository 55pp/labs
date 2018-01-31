#include "inspector.h"
#include "entity.h"
#include "level.h"
#include "loot.h"
#include "player.h"

Inspector::Inspector()
{
}

bool
Inspector::intersect(std::shared_ptr<Entity>&& a, std::shared_ptr<Entity>&& b)
{
  sf::FloatRect rect_a(static_cast<float>(a->position_x_),
                       static_cast<float>(a->position_y_), a->width_,
                       a->height_);
  sf::FloatRect rect_b(static_cast<float>(b->position_x_),
                       static_cast<float>(b->position_y_), b->width_,
                       b->height_);
  return rect_a.intersects(rect_b);
}

bool
Inspector::intersect(std::shared_ptr<Entity>&& a, Object& b)
{
  sf::FloatRect rect_a(static_cast<float>(a->position_x_),
                       static_cast<float>(a->position_y_), a->width_,
                       a->height_);
  return rect_a.intersects(b.rect);
}

bool
Inspector::intersectWithMap(std::shared_ptr<Entity>&& object,
                            std::vector<Object>& map)
{
  (void)object;
  (void)map;
  //    for(const auto& el : map){
  //        if(intersect(object, el)){

  //        }
  //    }
  return false;
}

bool
Inspector::intersectWithLoot(std::shared_ptr<Player>& actor,
                             std::shared_ptr<Loot>&& loot)
{
  if (intersect(actor, loot)) {
    loot->execute(actor);
    return true;
  }
  return false;
}
