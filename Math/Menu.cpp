#include "Menu.h"
#include <conio.h>
#include <iostream>
#include <iomanip>

Menu::Menu(char* a, char* b, char* c) : header(a), name(b), longestOption(strlen(c)) {
	MenuOption quit(c, "");
	menuOptions['q'] = quit;
}

void Menu::add(char* name, char* description) {
	MenuOption option(name, description);
	add(option);
}

void Menu::add(char* name, char* description, Menu* menu) {
	MenuOption option(name, description, menu);
	add(option);
}

void Menu::add(char* name, char* description, callback cb) {
	MenuOption option(name, description, cb);
	add(option);
}

void Menu::add(MenuOption option) {
	char key = 'a';
	while(key <= 'z') {
		if(menuOptions.find(key) == menuOptions.end()) {
			menuOptions[key] = option;
			if(strlen(option.name) > longestOption) longestOption = strlen(option.name);
			return;
		}
		key++;
	}
}

//Display the menu
void Menu::display() {
	system("cls"); //Clear screen - required

	//A short description of the menu
	std::cout << header << "\n\n";

	//Displayed above the menu
	std::cout << "-----------------------------------------------\n";
	std::cout << name << "\n";
	std::cout << "-----------------------------------------------\n\n";

	//Loop through all of our options and display them
	for (const auto &iter : menuOptions) {
		std::cout << iter.first << ".   " << std::setw(longestOption + 2) << std::left << iter.second.name << iter.second.description << "\n";
	}

	std::cout << "\nPlease choose an option to continue...";

	//Wait for user input and validate it
	char option;
	do {
		option = _getch();
	} while(!isValidOption(option));
	select(option); //Then, do something with it
}

bool Menu::isValidOption(char option) {
	//First we check if the character is an alphabetical character
	if(option < 'A' || (option > 'Z' && option < 'a') || option > 'z') return false;
	//Then we check if either it or its lowercase version are in our map
	return menuOptions.find((option < 'a' ? option + ('a' - 'A') : option)) != menuOptions.end();
}

void Menu::select(char _option) {
	if(!isValidOption(_option)) return;
	//Get our option
	MenuOption option = menuOptions[(_option < 'a' ? _option + ('a' - 'A') : _option)];
	
	//Now, we should check what to do
	//The only option that has no callback or menu should be the quit option
	if (option.cb == NULL) {
		if (option.menu == NULL) {
			//We should only be here if the quit option has been selected
			//So if there's a parent menu, let's head back to there
			//Otherwise quit the program
			return;
		}
		//No callback, and we're not the quit option
		//So display the sub-menu
		option.menu -> display();
	} else {
		//We have a function to call, so first we'll prompt the user for their preferred method of math (float or int)
		askForInput(option);
	}
	display(); // IMPORTANT - Displays menu again after sub-menus are finished running
}

//This function will display a switch for the user to toggle with arrow keys and accept with enter
void Menu::askForInput(MenuOption option) {
	bool intSelected = true;
	while (true) {
		//Clear the line and start again with the new option
		//Creates the "toggle" effect
		std::cout << "\rPlease select your output: ";
		std::cout << (intSelected ? "[integer]" : " integer ") << " " << (intSelected ? " float " : "[float]");
		
		//Wait for user input
		//If enter, we'll accept that option and then call the function with a boolean argument
		//The boolean argument decides whether the function should operate in integer mode or not
		//Otherwise, if the user hits the left or right arrow keys, we'll swap that toggle switch
		switch (_getch()) {
			case 13: //ENTER
				std::cout << "\n";
				option.cb(intSelected);
				_getch();
				return;
			case 224: //ARROW KEYS
				switch (_getch()) {
					case 75: //LEFT
					case 77: //RIGHT
						intSelected = !intSelected;
						break;
				}
				break;
		}
	}	
}