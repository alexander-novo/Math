#include "MenuOption.h"

MenuOption::MenuOption(char* a, char* b, Menu* c) : name(a), description(b), menu(c), cb(NULL) {}