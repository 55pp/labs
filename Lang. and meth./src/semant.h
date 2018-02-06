#ifndef SEMANT_H
#define SEMANT_H
#include "defin.h"
#include <string>
// class Semant
//{
// public:
//    Semant();
//};

const int EMPTY = -1;

enum DATA_TYPE
{
  TYPE_UNKNOW,
  TYPE_DOUBLE,
  TYPE_BOOL,
  TYPE_INT,
  TYPE_SWITCH,
  TYPE_BLOCK,
  TYPE_TYPEDEF
};

enum TDataType
{
  DataInt,
  DataDouble,
  DataBool
};

union TDataValue
{
  int dataAsInt;
  int* arrayDataAsInt;
  double dataAsDouble;
  double* arrayDataAsDouble;
};

struct TData
{
  TDataValue dataValue;
  TDataType dataType;
};

struct Node
{
  Lexem id;
  DATA_TYPE dataType;
  char* data;
  TData value;
  int size;
  Lexem type_name;
};

class Tree
{
  Node* n;
  Tree* up;
  Tree* left;
  Tree* right;

public:
  static Tree* cur;
  Tree(Tree* l, Tree* r, Tree* u, Node* data);
  Tree();
  ~Tree() {}
  void SetLeft(Node* data);
  void SetRight(Node* data);
  Tree* FindUp(Tree* from, Lexem id);
  Tree* FindUpOneLevel(Tree* from, Lexem id);
  Tree* FindUp(Lexem id);
  void Print();
  void SetCur(Tree* a);
  Tree* GetCur();
  int findTypeName(Lexem id);
  Tree* SemInclude(Lexem a, DATA_TYPE t);
  Tree* SemInclude(Lexem a, DATA_TYPE t, Lexem tn, int s = -1);
  void SemSetType(Tree* addr, DATA_TYPE t);
  void SemSetData(Tree* addr, Lexem data);
  int DupControl(Tree* addr, Lexem a);
  Tree* SetEmptyLeft();
  Tree* SetEmptyRight();
  Tree* GetLeft();
  Tree* GetRight();
  DATA_TYPE checkTypeAssign(DATA_TYPE a, DATA_TYPE b);
  DATA_TYPE checkTypeExpr(DATA_TYPE a, DATA_TYPE b);
  DATA_TYPE checkVar(Tree* var, int size);
};

#endif // SEMANT_H
