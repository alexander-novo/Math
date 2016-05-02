#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

class Menu;
typedef void(*callback)(bool);

#include <map>
#include "MenuOption.h"

class Menu {
	private:
		const char* header;
		const char* name;

		std::size_t longestOption;
		std::map<char, MenuOption> menuOptions;

		void askForInput(MenuOption);
	public:
		Menu(char* a, char* b) : Menu(a, b, "Return to Main Menu") {}
		Menu(char*, char*, char*);
		void add(char*, char*);
		void add(char*, char*, Menu*);
		void add(char*, char*, callback);
		void add(MenuOption);
		void display();
		bool isValidOption(char);
		void select(char);
};

#endif