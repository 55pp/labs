#include "semant.h"
#include "cstring"
#include "stdio.h"
#include <iostream>

// Semant::Semant()
//{

//}

Tree* Tree::cur = static_cast<Tree*>(NULL);

inline size_t
max(Lexem a, Lexem b)
{
  size_t size_a = strlen(a);
  size_t size_b = strlen(b);
  return size_a > size_b ? size_a : size_b;
}

Tree::Tree(Tree* l, Tree* r, Tree* u, Node* data)
{
  n = new Node();
  n->dataType = DATA_TYPE::TYPE_UNKNOW;
  strcpy(n->id, "");
  up = u;
  left = l;
  right = r;
  memcpy(n, data, sizeof(struct Node));
  //  *n = *data;
}

Tree::Tree()
{
  n = new Node();
  n->dataType = static_cast<DATA_TYPE>(EMPTY);
  //  n->data = "root";
  n->size = -1;
  strcpy(n->id, "root");
  strcpy(n->type_name, "root");
  Lexem t;
  strcpy(t, "root");
  //  n->id = static_cast<Lexem>(t);
  up = nullptr;
  left = nullptr;
  right = nullptr;
}

void
Tree::SetLeft(Node* data)
{
  left = new Tree(NULL, NULL, this, data);
}

void
Tree::SetRight(Node* data)
{
  right = new Tree(NULL, NULL, this, data);
}

Tree*
Tree::FindUp(Tree* from, Lexem id)
{
  Tree* i = from;
  //  while ((i != nullptr) && (memcmp(id, i->n->id, max(i->n->id, id)) != 0)) {
  //    i = i->up;
  //  }
  while (i != nullptr) {
    if (strcmp(id, i->n->id) == 0)
      return i;
    i = i->up;
  }
  return i;
}

Tree*
Tree::FindUpOneLevel(Tree* from, Lexem id)
{
  Tree* i = from;
  while (i != nullptr) {
    if (i->up != nullptr)
      if (i->up->right == i)
        break;
    if (strcmp(id, i->n->id) == 0)
      return i;
    i = i->up;
  }
  return nullptr;
}

Tree*
Tree::FindUp(Lexem id)
{
  return FindUp(cur, id);
}

void
Tree::Print()
{
  printf("Вершина с данными %s ----> %s", n->id, n->type_name);
  //  std::cout << "Вершина с данными " << n->id << "----->" << n->type_name;
  if (left != NULL)
    printf("       <слева данные %s", left->n->id);
  if (right != NULL)
    printf("       >справа данные %s", right->n->id);
  printf("\n");
  if (left != NULL)
    left->Print();
  if (right != NULL)
    right->Print();
}

void
Tree::SetCur(Tree* a)
{
  cur = a;
}

Tree*
Tree::GetCur()
{
  return cur;
}

int
Tree::findTypeName(Lexem id)
{
  Tree* i = cur;
  while (i != nullptr) {
    if (strcmp(id, i->n->id) == 0 && i->n->dataType == TYPE_TYPEDEF)
      return i->n->size;
    i = i->up;
  }
  return -1;
}

Tree*
Tree::SemInclude(Lexem a, DATA_TYPE t, Lexem tn, int s)
{
  if (DupControl(cur, a)) {
    std::cerr << "Тип не может быть идентификатором: " << a << std::endl;
    exit(0);
  }
  //  Tree* v;
  Node b;
  memcpy(b.id, a, strlen(a) + 1);
  b.dataType = t;
  strcpy(b.type_name, tn);
  //  strcpy(b.type_name, tn);
  //  b.type_name = std::move(tn);
  b.size = s;
  cur->SetLeft(&b);
  cur = cur->left;
  return cur;
}

void
Tree::SemSetData(Tree* addr, Lexem data)
{
  addr->n->data = data;
}

Tree*
Tree::SemInclude(Lexem a, DATA_TYPE t)
{
  if (DupControl(cur, a)) {
    std::cerr << "Повторное описание идентификатора: " << a << std::endl;
    exit(0);
  }
  //  Tree* v;
  Node b;
  memcpy(b.id, a, strlen(a) + 1);
  b.dataType = t;
  b.data = NULL;
  b.size = 0;
  if (t == DATA_TYPE::TYPE_DOUBLE) {
    strcpy(b.type_name, "double");
    //    b.type_name = "double";
  } else if (t == DATA_TYPE::TYPE_BOOL) {
    strcpy(b.type_name, "bool");
    //    b.type_name = "bool";
  }
  cur->SetLeft(&b);
  cur = cur->left;
  return cur;
}

int
Tree::DupControl(Tree* addr, Lexem a)
{
  if (FindUpOneLevel(addr, a) == NULL)
    return 0;
  return 1;
}

Tree*
Tree::SetEmptyLeft()
{
  Node b;
  strcpy(b.id, "null");
  b.dataType = static_cast<DATA_TYPE>(EMPTY);
  b.data = NULL;
  b.size = -1;
  strcpy(b.type_name, "node");
  //  b.type_name = "node";
  cur->SetLeft(&b);
  cur = cur->left;
  return cur;
}

Tree*
Tree::SetEmptyRight()
{
  Node b;
  strcpy(b.id, "null");
  b.dataType = static_cast<DATA_TYPE>(EMPTY);
  b.data = NULL;
  b.size = -1;
  strcpy(b.type_name, "node");
  //  b.type_name = "node";
  cur->SetRight(&b);
  cur = cur->right;
  return cur;
}

Tree*
Tree::GetLeft()
{
  return cur->left;
}

Tree*
Tree::GetRight()
{
  return cur->right;
}

DATA_TYPE
Tree::checkTypeAssign(DATA_TYPE a, DATA_TYPE b)
{
  if ((a == b) && a == DATA_TYPE::TYPE_TYPEDEF)
    return DATA_TYPE::TYPE_TYPEDEF;
  else if (a == DATA_TYPE::TYPE_BOOL && b != DATA_TYPE::TYPE_TYPEDEF)
    return DATA_TYPE::TYPE_BOOL;
  else if (a == DATA_TYPE::TYPE_DOUBLE && b != DATA_TYPE::TYPE_TYPEDEF)
    return DATA_TYPE::TYPE_DOUBLE;
  else
    return DATA_TYPE::TYPE_UNKNOW;
}

DATA_TYPE
Tree::checkTypeExpr(DATA_TYPE a, DATA_TYPE b)
{
  if (a == DATA_TYPE::TYPE_TYPEDEF || b == DATA_TYPE::TYPE_TYPEDEF)
    return DATA_TYPE::TYPE_UNKNOW;
  else if (a == b)
    return a;
  else if (a == DATA_TYPE::TYPE_DOUBLE || b == DATA_TYPE::TYPE_DOUBLE)
    return DATA_TYPE::TYPE_DOUBLE;
  else if (a == DATA_TYPE::TYPE_INT || b == DATA_TYPE::TYPE_INT)
    return DATA_TYPE::TYPE_INT;
  else
    return DATA_TYPE::TYPE_BOOL;
}

DATA_TYPE
Tree::checkVar(Tree* var, int size)
{
  if (var->n->dataType != DATA_TYPE::TYPE_TYPEDEF &&
      (var->n->size == size && size == 0))
    return var->n->dataType;
  else if (var->n->size != size)
    return DATA_TYPE::TYPE_UNKNOW;
  else {
    Tree* node = var;
    for (int i = 0; i < size; ++i) {
      if (node->up != nullptr)
        node = node->FindUp(node->n->type_name);
      else
        return DATA_TYPE::TYPE_UNKNOW;
    }
    if (node == nullptr) {
      return DATA_TYPE::TYPE_UNKNOW;
    }
    if (strcmp(node->n->type_name, "double") == 0) {
      return DATA_TYPE::TYPE_DOUBLE;
    } else if (strcmp(node->n->type_name, "bool") == 0) {
      return DATA_TYPE::TYPE_BOOL;
    } else if (strcmp(node->n->type_name, "int") == 0) {
      return DATA_TYPE::TYPE_INT;
    }
  }
}
