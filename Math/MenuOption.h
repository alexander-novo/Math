#ifndef __MENUOPTION_H_INCLUDED__
#define __MENUOPTION_H_INCLUDED__

class MenuOption;

#include "Menu.h"

class MenuOption {
	friend class Menu;
	private:
		callback cb;
		Menu* menu;

		const char* name;
		const char* description;

		MenuOption(char* a, char* b) : name(a), description(b), cb(NULL), menu(NULL){}
		MenuOption(char* a, char* b, callback c) : name(a), description(b), cb(c) , menu(NULL){}
		MenuOption(char*, char*, Menu*);
	public:
		MenuOption() : name("Error"), description("Error") {}
};

#endif