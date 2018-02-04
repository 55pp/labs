#include "diagram.h"
#include "ll1.h"
#include "scanner.h"
#include <defin.h>
#include <iostream>

using namespace std;

int
main(int argc, char* argv[])
{
  Scanner* sc;
  int type;
  Lexem l;
  if (argc <= 1)
    sc =
      new Scanner("/home/konstantin/QtProjects/Lang. and meth./src/input.txt");
  else
    sc = new Scanner(argv[1]);

  LL1 ll(sc);
  ll.LL_1();

  // Diagram dg(sc);
  //  do {
  //    type = sc->scan(l);
  //    cout << l << " - тип " << type << endl;
  //  } while (type != LEnd);
  // dg.program();

  return 0;
}
