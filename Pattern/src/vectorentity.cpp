#include "vectorentity.h"

VectorEntity::VectorEntity()
{
}

// bool
// isDie(std::shared_ptr<Entity> el)
//{
//  return !el->life_;
//}

int
VectorEntity::allUpdate(const double& time)
{
  //  vec.erase(std::remove_if(vec.begin(), vec.end(), isDie), vec.end());
  //  for (auto& el : vec) {
  //    //    if (el->position_x > 700)
  //    //      el->life = false;
  //    //    el->update(time);
  //    el.get()->update(time);
  //    //    std::cout << el->position_x << " " << el->position_y << std::endl;
  //  }
  EntytiIterator iter(vec);
  for (; iter.isDone(); iter.next()) {
    (iter.currentItem())->update(time);
  }
  return 0;
}

int
VectorEntity::drawEntities(sf::RenderWindow& window)
{
  for (auto& el : vec) {
    window.draw(el->getPicture());
  }
  return 0;
}

int
VectorEntity::push(std::shared_ptr<Entity> entity)
{
  vec.push_back(entity);
  return 0;
}
