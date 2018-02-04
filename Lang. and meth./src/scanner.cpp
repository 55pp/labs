#include "scanner.h"

Scanner::Scanner()
{
}

Scanner::Scanner(std::string file_name)
{
  setIndexCurrentSym(0);
  getData(file_name);
}

Scanner::~Scanner()
{
}

int
Scanner::scan(Lexem lexem)
{
  bool comment = false;
  int length_lexem;
  for (length_lexem = 0; length_lexem < MAX_LENGTH_LEX; ++length_lexem) {
    lexem[length_lexem] = 0;
  }
  length_lexem = 0;
  do {
    comment = false;
    while (text[indexCurrentSym] == ' ' || text[indexCurrentSym] == '\n' ||
           text[indexCurrentSym] == '\t') {
      //++pos;
      if (text[indexCurrentSym] == '\n') {
        ++line;
        pos = indexCurrentSym;
      }
      ++indexCurrentSym;
    }
    if (text[indexCurrentSym] == '/' && text[indexCurrentSym + 1] == '/') {
      indexCurrentSym += 2;
      while (text[indexCurrentSym] != '\n' && text[indexCurrentSym] != '#')
        ++indexCurrentSym;
      comment = true;
    }
  } while (comment);
  if (text[indexCurrentSym] == '\0') {
    lexem[0] = '#';
    return LEnd;
  }
  if (isNumber()) {
    lexem[length_lexem++] = text[indexCurrentSym++];
    while (isNumber())
      if (length_lexem < MAX_LENGTH_LEX - 1)
        lexem[length_lexem++] = text[indexCurrentSym++];
      else {
        indexCurrentSym++;
      }
    if (text[indexCurrentSym] == '.') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return isDouble(lexem, length_lexem);
    }
    if (lexem[20] != 0) {
      printError("Неверная константа", "");
      return LError;
    }
    return LConstInt10;
  } else if (isSmallLetter() || isBigLetter()) {
    lexem[length_lexem++] = text[indexCurrentSym++];
    while (isNumber() || isSmallLetter() || isBigLetter())
      if (length_lexem < MAX_LENGTH_LEX - 1)
        lexem[length_lexem++] = text[indexCurrentSym++];
      else {
        indexCurrentSym++;
      }
    for (int j = 0; j < MAX_KEY_WORD; ++j) {
      if (strcmp(lexem, keyword[j]) == 0)
        return index_keyword[j];
    }
    return LID;
  } else if (text[indexCurrentSym] == '.') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (isNumber()) {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return isDouble(lexem, length_lexem);
    }
    return LPoint;
  } else if (text[indexCurrentSym] == ',') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LComma;
  } else if (text[indexCurrentSym] == ':') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LDoublePoint;
  } else if (text[indexCurrentSym] == ';') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LSemicolon;
  } else if (text[indexCurrentSym] == '(') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LOpenRoundBraket;
  } else if (text[indexCurrentSym] == ')') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LCloseRoundBraket;
  } else if (text[indexCurrentSym] == '{') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LOpenBraket;
  } else if (text[indexCurrentSym] == '}') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LCloseBraket;
  } else if (text[indexCurrentSym] == '[') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LOpenSquareBraket;
  } else if (text[indexCurrentSym] == ']') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    return LCloseSquareBraket;
  } else if (text[indexCurrentSym] == '+') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LAddAssign;
    }
    return LAdd;
  } else if (text[indexCurrentSym] == '-') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LSubAssign;
    }
    return LSub;
  } else if (text[indexCurrentSym] == '*') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LMultAssign;
    }
    return LMult;
  } else if (text[indexCurrentSym] == '/') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LDivAssign;
    }
    return LDiv;
  } else if (text[indexCurrentSym] == '&') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LAndAssign;
    }
    return LAnd;
  } else if (text[indexCurrentSym] == '^') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LXorAssign;
    }
    return LXor;
  } else if (text[indexCurrentSym] == '|') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LOrAssign;
    }
    return LOr;
  } else if (text[indexCurrentSym] == '>') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LMoreEqual;
    } else if (text[indexCurrentSym] == '>') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LRightShift;
    }
    return LMore;
  } else if (text[indexCurrentSym] == '<') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LLessEqual;
    } else if (text[indexCurrentSym] == '<') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LLeftShift;
    }
    return LLess;
  } else if (text[indexCurrentSym] == '=') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LEqual;
    }
    return LAssign;
  } else if (text[indexCurrentSym] == '!') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '=') {
      lexem[length_lexem++] = text[indexCurrentSym++];
      return LNotEqual;
    }
    return -1;
  } else {
    printError("Неверный символ", lexem);
    indexCurrentSym++;
    return LError;
  }
}

void
Scanner::printError(std::string err, std::string a)
{
  if (a[0] == '\0') {
    std::cout << "Ошибка: " << err << " " << a << "(" << line << ", "
              << (indexCurrentSym - pos) << ")" << std::endl;
  } else {
    std::cout << "Ошибка: " << err << ". Неверный символ " << a << "(" << line
              << ", " << (indexCurrentSym - pos) << ")" << std::endl;
  }
  exit(0);
}

void
Scanner::printError(std::string err)
{
  std::cout << err << std::endl;
  exit(0);
}

void
Scanner::getData(std::string file_name)
{
  std::ifstream in(file_name);
  if (!in.is_open()) {
    printError("Отсутствует входной файл", "");
  }
  int i = 0;
  char a;
  in >> std::noskipws;
  while (!in.eof()) {
    in >> a;
    if (!in.eof())
      text[i++] = a;
    if (i > MAX_LENGTH_TEXT - 1) {
      in.close();
      printError("Слишком большой размер исходного модуля", "");
    }
  }
  text[i] = '\0';
  in.close();
}

bool
Scanner::isNumber()
{
  return (text[indexCurrentSym] <= '9' && text[indexCurrentSym] >= '0');
}

bool
Scanner::isSmallLetter()
{
  return (text[indexCurrentSym] >= 'a' && text[indexCurrentSym] <= 'z');
}

bool
Scanner::isBigLetter()
{
  return (text[indexCurrentSym] >= 'A' && text[indexCurrentSym] <= 'Z');
}

int
Scanner::isDouble(Lexem lexem, int& length_lexem)
{
  while (isNumber()) {
    if (length_lexem < MAX_LENGTH_LEX - 1)
      lexem[length_lexem++] = text[indexCurrentSym++];
    else {
      indexCurrentSym++;
    }
  }
  if (text[indexCurrentSym] == 'e' || text[indexCurrentSym] == 'E') {
    lexem[length_lexem++] = text[indexCurrentSym++];
    if (text[indexCurrentSym] == '+' || text[indexCurrentSym] == '-')
      lexem[length_lexem++] = text[indexCurrentSym++];
    if (isNumber()) {
      if (length_lexem < MAX_LENGTH_LEX - 1)
        lexem[length_lexem++] = text[indexCurrentSym++];
      else {
        indexCurrentSym++;
      }
      while (isNumber()) {
        if (length_lexem < MAX_LENGTH_LEX - 1)
          lexem[length_lexem++] = text[indexCurrentSym++];
        else {
          indexCurrentSym++;
        }
      }
      if (lexem[20] != 0) {
        printError("Неверная константа", "");
        return LError;
      }
      return LConstExp;
    } else {
      printError("Неверная константа", lexem);
    }
  } else
    printError("Неверная константа", lexem);
}

int
Scanner::getIndexCurrentSym()
{
  save_line = line;
  return indexCurrentSym;
}

void
Scanner::setIndexCurrentSym(int value)
{
  indexCurrentSym = value;
  pos = value;
  line = save_line;
}
