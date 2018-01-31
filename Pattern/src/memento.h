#ifndef MEMENTO_H
#define MEMENTO_H
#include <memory>

class ListEntities;
class Memento
{
public:
  Memento(ListEntities& list);
  std::shared_ptr<ListEntities> returnState();

private:
  std::shared_ptr<ListEntities> reserv_;
};

#endif // MEMENTO_H
