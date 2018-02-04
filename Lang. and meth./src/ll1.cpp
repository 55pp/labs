#include "ll1.h"
#include "defin.h"
#include "scanner.h"
#include <string>

LL1::LL1(Scanner* scanner)
{
  scanner_ = scanner;
}

void
LL1::program(int t)
{
  std::clog << "Program" << std::endl;
  if (t == LTypedef) {
    m[z++] = PROGRAM;
    m[z++] = TYPEDEF;
  } else if (t == LInt) {
    m[z++] = PROGRAM;
    m[z++] = MAIN;
  } else if (t == LBool || t == LID || t == LDouble) {
    m[z++] = PROGRAM;
    m[z++] = DESCRIPRION_DATE;
  } else if (t == LEnd) {
    m[z++] = END_PROGRAM;
  }
}

void
LL1::typedef_f()
{
  std::clog << "Typedef" << std::endl;
  m[z++] = LSemicolon;
  m[z++] = LCloseSquareBraket;
  m[z++] = LConstInt10;
  m[z++] = LOpenSquareBraket;
  m[z++] = LID;
  m[z++] = TYPE;
  m[z++] = LTypedef;
}

void
LL1::descriptionDate()
{
  std::clog << "Description date" << std::endl;
  m[z++] = LSemicolon;
  m[z++] = LIST_ELEMENTS;
  m[z++] = TYPE;
}

void
LL1::main_f()
{
  std::clog << "Main" << std::endl;
  m[z++] = BLOCK;
  m[z++] = LCloseRoundBraket;
  m[z++] = LOpenRoundBraket;
  m[z++] = LMethodMain;
  m[z++] = LInt;
}

void
LL1::operators(int t)
{
  std::clog << "Operators" << std::endl;
  if (t == LTypedef) {
    m[z++] = OPERATORS;
    m[z++] = TYPEDEF;
  } else if (t == LBool || t == LDouble) {
    m[z++] = OPERATORS;
    m[z++] = DESCRIPRION_DATE;
  } else if (t == LID) {
    auto ptr = scanner_->getIndexCurrentSym();
    Lexem l;
    auto t1 = scanner_->scan(l);
    if (t1 == LID) {
      m[z++] = OPERATORS;
      m[z++] = DESCRIPRION_DATE;
    } else {
      m[z++] = OPERATORS;
      m[z++] = ASSIGN;
      m[z++] = OPERAND;
    }
    scanner_->setIndexCurrentSym(ptr);
  } else if (t == LOpenBraket || t == LSwitch || t == LBreak || t == LCase ||
             t == LDefault) {
    m[z++] = OPERATORS;
    m[z++] = OPERATOR;
  } /*else if (t == LCloseBraket) {
    epsilon();
  }*/
  //  else if (t == LEnd) {
  //    m[z++] = END_PROGRAM;
  //  }
}

void
LL1::operator_f(int t)
{
  std::clog << "Operator" << std::endl;
  if (t == LAssign) {
    m[z++] = ASSIGN;
  } else if (t == LOpenBraket) {
    m[z++] = BLOCK;
  } else if (t == LCloseBraket) {
    m[z++] = LCloseBraket;
    //    epsilon();
  } else if (t == LSwitch) {
    m[z++] = SWITCH;
  } else if (t == LBreak) {
    m[z++] = LSemicolon;
    m[z++] = LBreak;
  } else if (t == LCase) {
    //    m[z++] = CASE;
    epsilon();
  } else if (t == LDefault) {
    m[z++] = DEFAULT_SWITCH;
  } else if (t == LComma) {
  } else if (t == LEnd) {
    m[z++] = END_PROGRAM;
  }
}

void
LL1::list_elements(int t)
{
  std::clog << "List elements" << std::endl;
  if (t == LID) {
    m[z++] = K;
    m[z++] = ELEMENT;
  }
}

void
LL1::k(int t)
{
  std::clog << "K" << std::endl;
  if (t == LComma) {
    m[z++] = K;
    m[z++] = ELEMENT;
    m[z++] = LComma;
  } /*else if (t == LSemicolon) {
    epsilon();
    //    m[z++] = LSemicolon;
  }*/
}

void
LL1::element(int t)
{
  std::clog << "Element" << std::endl;
  if (t == LID) {
    m[z++] = Q;
    m[z++] = LID;
  }
}

void
LL1::type_f(int t)
{
  if (t == LBool) {
    m[z++] = LBool;
  } else if (t == LDouble) {
    m[z++] = LDouble;
  } else if (t == LID) {
    m[z++] = LID;
  }
}

void
LL1::q(int t)
{
  if (t == LSemicolon) {
    epsilon();
    //    m[z++] = LSemicolon;
  } else if (t == LAssign) {
    m[z++] = W;
    m[z++] = LAssign;
  }
}

void
LL1::w(int t)
{
  if (t == LID) {
    m[z++] = LID;
  } else if (t == LOpenBraket) {
    m[z++] = LCloseBraket;
    m[z++] = LIST;
    m[z++] = LOpenBraket;
  } else if (t == LConstExp) {
    m[z++] = EXPRESS;
  } else if (t == LConstInt10) {
    //    m[z++] = LConstInt10;
    m[z++] = EXPRESS;
  } else if (t == LTrue) {
    m[z++] = EXPRESS;
  } else if (t == LFalse) {
    m[z++] = EXPRESS;
  }
}

void
LL1::block(int t)
{
  if (t == LOpenBraket) {
    m[z++] = LCloseBraket;
    m[z++] = OPERATORS;
    m[z++] = LOpenBraket;
  }
}

void
LL1::list(int t)
{
  if (t == LConstExp || t == LConstInt10 || t == LID || t == LTrue ||
      t == LFalse) {
    m[z++] = WK;
    m[z++] = OPERAND;
  }
}

void
LL1::wk(int t)
{
  if (t == LComma) {
    m[z++] = WK;
    m[z++] = OPERAND;
    m[z++] = LComma;
  }
}

void
LL1::case_2(int t)
{
  if (t == LCase) {
    m[z++] = CASE_2;
    m[z++] = CASE;
  } else if (t == LDefault) {
    m[z++] = DEFAULT_SWITCH;
  }
}

void
LL1::operand(int t)
{
  if (t == LID) {
    m[z++] = R;
    m[z++] = LID;
  } else if (t == LConstExp) {
    m[z++] = LConstExp;
  } else if (t == LConstInt10) {
    m[z++] = LConstInt10;
  } else if (t == LTrue) {
    m[z++] = LTrue;
  } else if (t == LFalse) {
    m[z++] = LFalse;
  } else if (t == LOpenBraket) {
    m[z++] = LCloseBraket;
    m[z++] = LIST;
    m[z++] = LOpenBraket;
  } else if (t == LOpenSquareBraket) {
    m[z++] = R;
  } /*else {
    epsilon();
  }*/
}

void
LL1::r(int t)
{
  if (t == LOpenSquareBraket) {
    m[z++] = R;
    m[z++] = LCloseSquareBraket;
    m[z++] = EXPRESS;
    m[z++] = LOpenSquareBraket;
  } /*else {
    epsilon();
  }*/
}

void
LL1::comparsion(int t)
{
  if (t == LMore) {
    m[z++] = LMore;
  } else if (t == LLess) {
    m[z++] = LLess;
  } else if (t == LMoreEqual) {
    m[z++] = LMoreEqual;
  } else if (t == LLessEqual) {
    m[z++] = LLessEqual;
  } else if (t == LEqual) {
    m[z++] = LEqual;
  } else if (t == LNotEqual) {
    m[z++] = LNotEqual;
  }
}

void
LL1::computation(int t)
{
  if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
      t == LFalse) {
    m[z++] = B;
    m[z++] = OR;
  }
}

int
LL1::LL_1()
{
  int t;
  int fl = 1;
  //  int i;
  //  int uk1;
  //  int ttt;
  Lexem l;
  //  char sss[30];
  m[z] = PROGRAM;
  t = scanner_->scan(l);
  while (fl) {
    if (m[z] < PROGRAM) {
      if (m[z] == t) {
        if (t == LEnd)
          fl = 0;
        else {
          t = scanner_->scan(l);
          z--;
        }
      } else {
        scanner_->printError("Неверный символ", l);
        return EXIT_FAILURE;
      }
    } else {
      std::clog << l << std::endl;
      switch (m[z]) {
        case PROGRAM:
          program(t);
          break;
        case TYPEDEF:
          typedef_f();
          break;
        case DESCRIPRION_DATE:
          descriptionDate();
          break;
        case MAIN:
          main_f();
          break;
        case OPERATORS:
          operators(t);
          break;
        case OPERATOR:
          operator_f(t);
          break;
        case TYPE:
          type_f(t);
          break;
        case LIST_ELEMENTS:
          list_elements(t);
          break;
        case K:
          k(t);
          break;
        case ELEMENT:
          element(t);
          break;
        case Q:
          q(t);
          break;
        case W:
          w(t);
          break;
        case BLOCK:
          block(t);
          break;
        case LIST:
          list(t);
          break;
        case OPERAND:
          operand(t);
          break;
        case WK:
          wk(t);
          break;
        case R:
          r(t);
          break;
        case ASSIGN:
          if (t == LAssign) {
            m[z++] = LSemicolon;
            m[z++] = EXPRESS;
            m[z++] = LAssign;
          }
          break;
        case EXPRESS:
          m[z++] = A;
          m[z++] = COMPUTATION;
          break;
        case A:
          if (t == LMore || t == LLess || t == LMoreEqual || t == LLessEqual ||
              t == LEqual || t == LNotEqual) {
            m[z++] = A;
            m[z++] = COMPUTATION;
            m[z++] = COMPARSION;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case COMPARSION:
          comparsion(t);
          break;
        case COMPUTATION:
          computation(t);
          break;
        case B:
          if (t == LOr) {
            m[z++] = B;
            m[z++] = OR;
            m[z++] = LOr;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case OR:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse) {
            m[z++] = C;
            m[z++] = XOR;
          }
          break;
        case C:
          if (t == LXor) {
            m[z++] = C;
            m[z++] = XOR;
            m[z++] = LXor;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case XOR:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse) {
            m[z++] = D;
            m[z++] = AND;
          }
          break;
        case D:
          if (t == LAnd) {
            m[z++] = D;
            m[z++] = AND;
            m[z++] = LAnd;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case AND:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse) {
            m[z++] = E;
            m[z++] = SHIFT;
          }
          break;
        case E:
          if (t == LLeftShift) {
            m[z++] = E;
            m[z++] = SHIFT;
            m[z++] = LLeftShift;
          } else if (t == LRightShift) {
            m[z++] = E;
            m[z++] = SHIFT;
            m[z++] = LRightShift;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case SHIFT:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse) {
            m[z++] = F;
            m[z++] = ARITHMETIC;
          }
          break;
        case F:
          if (t == LAdd) {
            m[z++] = F;
            m[z++] = ARITHMETIC;
            m[z++] = LAdd;
          } else if (t == LSub) {
            m[z++] = F;
            m[z++] = ARITHMETIC;
            m[z++] = LSub;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case ARITHMETIC:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse) {
            m[z++] = G;
            m[z++] = MUL_DIV;
          }
          break;
        case G:
          if (t == LMult) {
            m[z++] = G;
            m[z++] = MUL_DIV;
            m[z++] = LMult;
          } else if (t == LDiv) {
            m[z++] = G;
            m[z++] = MUL_DIV;
            m[z++] = LDiv;
          }
          //          else if (t == LCloseRoundBraket /*|| t == LSemicolon*/) {
          //            epsilon();
          //          }
          break;
        case MUL_DIV:
          if (t == LID || t == LConstExp || t == LConstInt10 || t == LTrue ||
              t == LFalse || t == LOpenRoundBraket) {
            m[z++] = BRACKETS;
          }
          break;
        case BRACKETS:
          if (t == LOpenRoundBraket) {
            m[z++] = LCloseRoundBraket;
            m[z++] = EXPRESS;
            m[z++] = LOpenRoundBraket;
          } else {
            m[z++] = OPERAND;
          }
          break;
        case END_PROGRAM:
          m[z++] = LEnd;
          fl = 0;
          break;
        case SWITCH:
          if (t == LSwitch) {
            m[z++] = SWITCH_2;
            m[z++] = Y;
          }
          break;
        case Y:
          if (t == LDefault) {
            m[z++] = DEFAULT_SWITCH;
          }
          break;
        case SWITCH_2:
          if (t == LSwitch) {
            //            m[z++] = LSemicolon;
            m[z++] = LCloseBraket;
            m[z++] = CASE_2;
            m[z++] = LOpenBraket;
            m[z++] = LCloseRoundBraket;
            m[z++] = EXPRESS;
            m[z++] = LOpenRoundBraket;
            m[z++] = LSwitch;
          }
          break;
        case CASE:
          if (t == LCase) {
            m[z++] = CASE_BLOCK;
            m[z++] = LDoublePoint;
            m[z++] = LConstInt10;
            m[z++] = LCase;
          }
          break;
        case CASE_BLOCK:
          if (t == LTypedef || t == LBool || t == LDouble || t == LID ||
              t == LOpenBraket || t == LSwitch) {
            m[z++] = OPERATORS;
          }
          break;
        case DEFAULT_SWITCH:
          if (t == LDefault) {
            m[z++] = CASE_BLOCK;
            m[z++] = LDoublePoint;
            m[z++] = LDefault;
          }
          break;
        case CASE_2:
          case_2(t);
          break;
      }
      z--;
    }
  }
  return EXIT_SUCCESS;
}

void
LL1::epsilon()
{
  z--;
}
