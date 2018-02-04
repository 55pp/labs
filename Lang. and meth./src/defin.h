#ifndef DEFIN_H
#define DEFIN_H

const int MAX_LENGTH_TEXT = 10000;
const int MAX_LENGTH_LEX = 22;
const int MAX_KEY_WORD = 12;

const int LID = 1;
const int LConstInt10 = 10;
const int LConstExp = 11;
const int LDefault = 18;
const int LInt = 19;
const int LMethodMain = 20;
const int LBool = 21;
const int LDouble = 22;
const int LReturn = 23;
const int LBreak = 24;
const int LSwitch = 25;
const int LCase = 26;
const int LTrue = 27;
const int LFalse = 28;
const int LTypedef = 29;
const int LAdd = 30;
const int LAddAssign = 31;
const int LSub = 32;
const int LSubAssign = 33;
const int LMult = 34;
const int LMultAssign = 35;
const int LDiv = 36;
const int LDivAssign = 37;
const int LAnd = 38;
const int LAndAssign = 39;
const int LXor = 40;
const int LXorAssign = 41;
const int LOr = 42;
const int LOrAssign = 43;
const int LAssign = 44;
const int LMore = 45;
const int LMoreEqual = 46;
const int LLess = 47;
const int LLessEqual = 48;
const int LEqual = 49;
const int LNotEqual = 50;
const int LPoint = 60;
const int LComma = 61;
const int LSemicolon = 62;
const int LDoublePoint = 63;
const int LLeftShift = 64;
const int LRightShift = 65;
const int LOpenRoundBraket = 70;
const int LCloseRoundBraket = 71;
const int LOpenBraket = 72;
const int LCloseBraket = 73;
const int LOpenSquareBraket = 74;
const int LCloseSquareBraket = 75;
const int LError = 900;
const int LEnd = 100;

typedef char SrcTxt[MAX_LENGTH_TEXT];
typedef char Lexem[MAX_LENGTH_LEX];

#endif // DEFIN_H
