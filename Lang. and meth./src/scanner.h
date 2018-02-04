#ifndef SCANNER_H
#define SCANNER_H
#include <cstring>
#include <defin.h>
#include <fstream>
#include <iostream>

class Scanner
{
public:
  Scanner();
  Scanner(std::string file_name);
  ~Scanner();

  int scan(Lexem lexem);
  void printError(std::string err, std::string a);
  void printError(std::string err);
  void getData(std::string file_name);
  inline bool isNumber();
  inline bool isSmallLetter();
  inline bool isBigLetter();
  int isDouble(Lexem lexem, int& length_lexem);

  int getIndexCurrentSym();
  void setIndexCurrentSym(int value);

private:
  SrcTxt text;
  int indexCurrentSym = 0;
  int line = 1;
  int save_line = 0;
  int pos = 0;
  Lexem keyword[MAX_KEY_WORD] = { "main",  "bool",    "double", "return",
                                  "break", "switch",  "case",   "true",
                                  "false", "typedef", "int",    "default" };
  int index_keyword[MAX_KEY_WORD] = {
    LMethodMain, LBool, LDouble, LReturn,  LBreak, LSwitch,
    LCase,       LTrue, LFalse,  LTypedef, LInt,   LDefault
  };
};

#endif // SCANNER_H
