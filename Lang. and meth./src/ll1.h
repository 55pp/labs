#ifndef LL1_H
#define LL1_H
#include "scanner.h"
#include <queue>

const int PROGRAM = 2000;
const int TYPEDEF = 2001;
const int MAIN = 2002;
const int BLOCK = 2003;
const int OPERATORS = 2004;
const int OPERATOR = 2005;
const int DESCRIPRION_DATE = 2006;
const int TYPE = 2007;
const int LIST_ELEMENTS = 2008;
const int K = 2009;
const int ELEMENT = 2010;
const int Q = 2011;
const int W = 2012;
const int EXPRESS = 2013;
const int A = 2014;
const int ASSIGN = 2015;
const int SWITCH = 2016;
const int LIST = 2017;
const int OPERAND = 2018;
const int WK = 2019;
const int R = 2020;
const int COMPUTATION = 2021;
const int COMPARSION = 2022;
const int B = 2023;
const int OR = 2024;
const int C = 2025;
const int XOR = 2026;
const int D = 2027;
const int AND = 2028;
const int E = 2029;
const int SHIFT = 2030;
const int F = 2031;
const int ARITHMETIC = 2032;
const int G = 2033;
const int MUL_DIV = 2034;
const int BRACKETS = 2035;
const int SWITCH_2 = 2036;
const int Y = 2037;
const int DEFAULT_SWITCH = 2038;
const int CASE = 2039;
const int CASE_BLOCK = 2040;
const int END_PROGRAM = 9000;
const int CASE_2 = 2041;
// const int  = 2000;
// const int PROGRAM = 2000;

class LL1
{
public:
  LL1(Scanner* scanner);
  int LL_1();

  void list(int t);

  void assign();

private:
  void epsilon();
  Scanner* scanner_;
  //  std::queue<int> m;
  int m[5000], z = 0;
  void program(int t);
  void typedef_f();
  void descriptionDate();
  void main_f();
  void operators(int t);
  void operator_f(int t);
  void list_elements(int t);
  void k(int t);
  void element(int t);
  void type_f(int t);
  void q(int t);
  void w(int t);
  void block(int t);
  void wk(int t);
  void operand(int t);
  void r(int t);
  void comparsion(int t);
  void computation(int t);
  void express();
  void a();
  void case_2(int t);
};

#endif // LL1_H
