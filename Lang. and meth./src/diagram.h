#ifndef DIAGRAM_H
#define DIAGRAM_H
#include "scanner.h"
#include "semant.h"

class Diagram
{
public:
  Diagram(Scanner* s);
  ~Diagram() {}
  void program();
  //  void block();
  void typedf();
  void descriptionData();
  void list(int size);
  DATA_TYPE expr();
  DATA_TYPE A();
  DATA_TYPE B();
  DATA_TYPE C();
  DATA_TYPE D();
  DATA_TYPE E();
  DATA_TYPE F();
  DATA_TYPE G();
  void operators();
  void sswitch();
  void sswitch_2();
  void case_();
  void assign();
  void err(std::string&& err);

private:
  Scanner* sc;
  Tree* root = nullptr;
};

#endif // DIAGRAM_H
