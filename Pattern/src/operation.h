#ifndef OPERATION_H
#define OPERATION_H

class Enemy;
class BigEnemy;
class Operation
{
public:
  virtual void visit(Enemy* target) = 0;
  //  virtual void visit(BigEnemy* target) = 0;
};

#endif // OPERATION_H
