#include "diagram.h"

Diagram::Diagram(Scanner* s)
  : sc(s)
{
  root = new Tree();
  root->SetCur(root);
}

void
Diagram::program()
{
  Lexem l;
  int t;
  int uk1;
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LTypedef || t == LBool || t == LDouble || t == LID || t == LInt) {
    if (t == LInt) {
      t = sc->scan(l);
      if (t != LMethodMain)
        sc->printError("Ожидалось слово main", l);
      t = sc->scan(l);
      if (t != LOpenRoundBraket)
        sc->printError("Ожидался символ (", l);
      t = sc->scan(l);
      if (t != LCloseRoundBraket)
        sc->printError("Ожидался символ )", l);
      t = sc->scan(l);
      if (t != LOpenBraket)
        sc->printError("Ожидался символ {", l);
      Tree* branch = root->GetCur();
      if (root->GetRight() == nullptr) {
        root->SetEmptyRight();
      } else {
        root->SetEmptyLeft();
        branch = root->GetCur();
        root->SetEmptyRight();
      }
      operators();
      t = sc->scan(l);
      if (t != LCloseBraket)
        sc->printError("Ожидался символ }", l);
      root->SetCur(branch);
    } else if (t == LTypedef) {
      sc->setIndexCurrentSym(uk1);
      // ветка: typedef
      typedf();
    } else {
      sc->setIndexCurrentSym(uk1);
      //ветка: описание данных
      descriptionData();
    }

    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  root->Print();
}

void
Diagram::typedf()
{
  Lexem l;
  int t;
  t = sc->scan(l);
  if (t != LTypedef)
    sc->printError("Ожидалось слово typedef", l);
  t = sc->scan(l);
  if (t != LBool && t != LDouble && t != LID)
    sc->printError("Ожидался один из вариантов: bool, double, <идентификатор>",
                   l);
  // проверка идентификатора как типа
  int size = 0;
  Lexem type_name;
  strcpy(type_name, l);
  if (t == LID) {
    size = root->findTypeName(l);
    if (size == -1)
      sc->printError("Неизвестый тип", l);
  }
  t = sc->scan(l);
  if (t != LID)
    sc->printError("Ожидался идентификатор", l);
  root->SemInclude(l, TYPE_TYPEDEF, type_name, size + 1);
  //  root->Print();
  t = sc->scan(l);
  if (t != LOpenSquareBraket)
    sc->printError("Ожидался символ [", l);
  t = sc->scan(l);
  if (t != LConstInt10)
    sc->printError("Ожидались цифры", l);
  t = sc->scan(l);
  if (t != LCloseSquareBraket)
    sc->printError("Ожидался символ ]", l);
  t = sc->scan(l);
  if (t != LSemicolon)
    sc->printError("Ожидался символ ;", l);
}

void
Diagram::descriptionData()
{
  Lexem l;
  int t;
  int uk1;
  t = sc->scan(l);
  if (t != LBool && t != LDouble && t != LID)
    sc->printError("Ожидался один из вариантов: bool, double, <идентификатор>",
                   l);

  DATA_TYPE var_type;
  int size = 0;
  Lexem type_name;
  if (t == LID) {
    // проверка typedef типа
    size = root->findTypeName(l);
    if (size == -1)
      sc->printError("Неизвестный тип", l);
    var_type = TYPE_TYPEDEF;
    strcpy(type_name, l);
  } else if (t == LBool) {
    var_type = TYPE_BOOL;
  } else {
    var_type = TYPE_DOUBLE;
  }

  do {
    t = sc->scan(l);
    if (t != LID)
      sc->printError("Ожидался идентификатор", l);

    // включение переменной в дерево
    if (var_type == TYPE_TYPEDEF) {
      root->SemInclude(l, var_type, type_name, size);
    } else if (var_type == TYPE_BOOL || var_type == TYPE_DOUBLE) {
      root->SemInclude(l, var_type);
    }

    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
    if (t == LAssign) {
      uk1 = sc->getIndexCurrentSym();
      t = sc->scan(l);
      if (t == LOpenBraket) {
        // ветка: список
        sc->setIndexCurrentSym(uk1);
        list(size);
        //        t = sc->scan(l);
        //        if (t != LCloseBraket)
        //          sc->printError("Ожидался символ }", l);
      } else {
        sc->setIndexCurrentSym(uk1);
        // ветка: выражение
        DATA_TYPE type_s;
        type_s = expr();
        var_type = root->checkTypeAssign(var_type, type_s);
        if (var_type != DATA_TYPE::TYPE_BOOL &&
            var_type != DATA_TYPE::TYPE_DOUBLE &&
            var_type != DATA_TYPE::TYPE_INT)
          //      err("Неверное обращение к массиву");
          sc->printError("Неверное обращение к массиву", l);
      }
      uk1 = sc->getIndexCurrentSym();
      t = sc->scan(l);
    }
  } while (t == LComma);
  sc->setIndexCurrentSym(uk1);
  t = sc->scan(l);
  if (t != LSemicolon)
    sc->printError("Ожидался символ ;", l);
}

void
Diagram::list(int size)
{
  Lexem l;
  int t;
  int uk1;
  int new_size = size;
  t = sc->scan(l);
  if (t != LOpenBraket)
    sc->printError("Ожидался символ {", l);
  new_size -= 1;
  if (new_size < 0) {
    sc->printError("Большая вложенность", l);
  }
  do {
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
    if (t == LOpenBraket) {
      sc->setIndexCurrentSym(uk1);
      list(new_size);
      t = sc->scan(l);
    } else if (t == LConstExp || t == LConstInt10 || t == LTrue ||
               t == LFalse) {
      t = sc->scan(l);
    } /*else {
      sc->printError("Ожидались константа или список", l);
    }*/

  } while (t == LComma);
  if (t != LCloseBraket)
    sc->printError("Ожидался символ }", l);
}

DATA_TYPE
Diagram::expr()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = A();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while ((t >= LMore) && (t <= LNotEqual)) {
    DATA_TYPE type_s;
    type_s = A();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::A()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = B();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LOr) {
    DATA_TYPE type_s;
    type_s = B();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::B()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = C();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LXor) {
    DATA_TYPE type_s;
    type_s = C();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::C()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = D();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LAnd) {
    DATA_TYPE type_s;
    type_s = D();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::D()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = E();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LLeftShift || t == LRightShift) {
    DATA_TYPE type_s;
    type_s = E();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::E()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = F();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LAdd || t == LSub) {
    DATA_TYPE type_s;
    type_s = F();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::F()
{
  Lexem l;
  int t;
  int uk1;
  DATA_TYPE type_f;
  type_f = G();
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LMult || t == LDiv) {
    DATA_TYPE type_s;
    type_s = G();
    type_f = root->checkTypeExpr(type_f, type_s);
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
  return type_f;
}

DATA_TYPE
Diagram::G()
{
  Lexem l;
  int t;
  int uk1;
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  if (t == LConstExp) {
    return DATA_TYPE::TYPE_DOUBLE;
  } else if (t == LConstInt10) {
    return DATA_TYPE::TYPE_INT;
  } else if (t == LTrue || t == LFalse) {
    return DATA_TYPE::TYPE_BOOL;
  } else if (t == LID) {
    Tree* var = root->FindUp(l);
    if (var == nullptr) {
      sc->printError("Необъявленная переменная", l);
    }
    int size = 0;
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
    while (t == LOpenSquareBraket) {
      DATA_TYPE type_expr = expr();
      if (type_expr != DATA_TYPE::TYPE_INT) {
        sc->printError("Неверный индекс", l);
        //        err("Неверный индекс");
      }
      t = sc->scan(l);
      if (t != LCloseSquareBraket)
        sc->printError("Ожидался символ ]", l);
      uk1 = sc->getIndexCurrentSym();
      t = sc->scan(l);
      ++size;
    }
    sc->setIndexCurrentSym(uk1);
    DATA_TYPE t_typedef = root->checkVar(var, size);
    if (t_typedef != DATA_TYPE::TYPE_BOOL &&
        t_typedef != DATA_TYPE::TYPE_DOUBLE && t_typedef != DATA_TYPE::TYPE_INT)
      //      err("Неверное обращение к массиву");
      sc->printError("Неверное обращение к массиву", l);
    sc->setIndexCurrentSym(uk1);
    return t_typedef;
  } else if (t == LOpenRoundBraket) {
    DATA_TYPE type = expr();
    t = sc->scan(l);
    if (t != LCloseRoundBraket)
      sc->printError("Ожидался символ )", l);
    return type;
  } else {
    sc->printError("Ожидалась константа или выражение", l);
  }
  return DATA_TYPE::TYPE_UNKNOW;
}

void
Diagram::operators()
{
  Lexem l;
  int t;
  int uk1;
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  while (t == LTypedef || t == LSwitch || t == LBreak || t == LOpenBraket ||
         t == LBool || t == LDouble || t == LID || t == LSemicolon) {
    if (t == LBreak) {
      t = sc->scan(l);
      if (t != LSemicolon)
        sc->printError("Ожидался символ ;", l);
    } else if (t == LTypedef) {
      sc->setIndexCurrentSym(uk1);
      typedf();
    } else if (t == LSwitch) {
      sc->setIndexCurrentSym(uk1);
      Tree* branch = root->GetCur();
      if (root->GetRight() == nullptr) {
        root->SetEmptyRight();
      } else {
        root->SetEmptyLeft();
        branch = root->GetCur();
        root->SetEmptyRight();
      }
      sswitch();
      root->SetCur(branch);
    } else if (t == LOpenBraket) {
      Tree* branch = root->GetCur();
      if (root->GetRight() == nullptr) {
        root->SetEmptyRight();
      } else {
        root->SetEmptyLeft();
        branch = root->GetCur();
        root->SetEmptyRight();
      }
      operators();
      t = sc->scan(l);
      if (t != LCloseBraket)
        sc->printError("Ожидался символ }", l);
      root->SetCur(branch);
    } else if (t == LSemicolon) {
    } else if (t == LID) {
      t = sc->scan(l);
      if (t == LID) {
        sc->setIndexCurrentSym(uk1);
        descriptionData();
      } else {
        sc->setIndexCurrentSym(uk1);
        assign();
      }
    } else if (t == LDouble || t == LBool) {
      sc->setIndexCurrentSym(uk1);
      descriptionData();
    }
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  }
  sc->setIndexCurrentSym(uk1);
}

void
Diagram::sswitch()
{
  Lexem l;
  int t;
  sswitch_2();
  t = sc->scan(l);
  if (t == LDefault) {
    t = sc->scan(l);
    if (t != LDoublePoint)
      sc->printError("Ожидался символ :", l);
    operators();
  }
  t = sc->scan(l);
  if (t != LCloseBraket)
    sc->printError("Ожидался символ }", l);
}

void
Diagram::sswitch_2()
{
  Lexem l;
  int t;
  int uk1;
  t = sc->scan(l);
  if (t != LSwitch)
    sc->printError("Ожидалось слово switch", l);
  t = sc->scan(l);
  if (t != LOpenRoundBraket)
    sc->printError("Ожидался символ (", l);
  expr();
  t = sc->scan(l);
  if (t != LCloseRoundBraket)
    sc->printError("Ожидался символ )", l);
  t = sc->scan(l);
  if (t != LOpenBraket)
    sc->printError("Ожидался символ {", l);
  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  if (t != LCase)
    sc->printError("Ожидалось слово case", l);
  do {
    sc->setIndexCurrentSym(uk1);
    case_();
    uk1 = sc->getIndexCurrentSym();
    t = sc->scan(l);
  } while (t == LCase);
  sc->setIndexCurrentSym(uk1);
}

void
Diagram::case_()
{
  Lexem l;
  int t;
  //  int uk1;
  t = sc->scan(l);
  if (t != LCase)
    sc->printError("Ожидалось слово case", l);
  t = sc->scan(l);
  if (t == LConstExp || t == LConstInt10 || t == LTrue || t == LFalse) {

  } else {
    sc->printError("Ожидалась константа", l);
  }
  t = sc->scan(l);
  if (t != LDoublePoint)
    sc->printError("Ожидался символ :", l);
  operators();
}

void
Diagram::assign()
{
  Lexem l;
  int t;
  //  int uk1;
  //  uk1 = sc->getIndexCurrentSym();
  t = sc->scan(l);
  if (t != LID)
    sc->printError("Ожидался идентификатор", l);
  Tree* var = root->FindUp(l);
  int size = 0;
  DATA_TYPE type_f;
  t = sc->scan(l);
  while (t == LOpenSquareBraket) {
    type_f = expr();
    if (type_f != DATA_TYPE::TYPE_INT) {
      sc->printError("Неверный индекс", l);
      //      err("Неверный индекс");
    }
    t = sc->scan(l);
    if (t != LCloseSquareBraket)
      sc->printError("Ожидался символ ]", l);
    t = sc->scan(l);
    ++size;
  }
  type_f = root->checkVar(var, size);
  if (type_f != DATA_TYPE::TYPE_BOOL && type_f != DATA_TYPE::TYPE_DOUBLE &&
      type_f != DATA_TYPE::TYPE_INT)
    // err("Неверное обращение к массиву");
    sc->printError("Неверное обращение к массиву", l);
  if (t != LAssign)
    sc->printError("Ожидался символ =", l);
  DATA_TYPE type_s;
  type_s = expr();
  t = sc->scan(l);
  type_f = root->checkTypeAssign(type_f, type_s);
  if (type_s == DATA_TYPE::TYPE_UNKNOW) {
    // err("Ошибка присваивания");
    sc->printError("Ошибка присваивания", l);
  }
  if (t != LSemicolon)
    sc->printError("Ожидался символ ;", l);
}

void
Diagram::err(std::string&& err)
{
  std::cout << err << std::endl;
  exit(0);
}
