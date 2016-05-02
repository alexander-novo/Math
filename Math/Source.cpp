int main();

void getFromInput(double&, char, bool);

//Math functions, grouped by menu

void sum(bool);
void sub(bool);
void mult(bool);
void div(bool);

void sqRt(bool);
void cbRt(bool);

void sqr(bool);
void cub(bool);

void circ(bool);
void rect(bool);
void tri(bool);

#include <iostream>
#include <iomanip>
#include <map>
#include <conio.h>

//My own class - simplifies menu creation;
#include "Menu.h"

using namespace std;

//Couldn't get the Math.h constant to work, so I made my own;
const double pi() { return std::atan(1) * 4; }

int main() {
	//Creation of menus
	Menu mainMenu("          MATH SKILLS PRACTICE PROGRAM\n\n      Hello, and welcome to the Math Skills\n      Practice Program.\n\n      This program allows you to practice your\n      math skills.\n\n      Choose what you want to practice in the\n      menu shown below.",
				  "                   MAIN MENU",
				  "Quit the Program");
	Menu arithmetic("     Hello, and welcome to the Basic Math\n     Skills Menu.\n\n     This menu allows you to select a basic\n     math skill to practice.",
					"            BASIC MATH SKILLS MENU");
	Menu roots("       Hello, and welcome to the Roots Menu.\n\n       This menu allows you to take a square\n       root of a number or take a cube root\n       a number.",
		       "                    ROOTS MENU");
	Menu powers("       Hello, and welcome to the Powers Menu.\n\n       This menu allows you to square a number\n       or cube a number.",
		        "                    POWERS MENU");
	Menu geometry("       Hello, and welcome to the Basic Geometry\n       Menu.\n\n       This menu allows you to perform basic\n       geometric calculations.",
		          "                BASIC GEOMETRY MENU");

	//Add options to the main menu
	//Each option will redirect to a sub-menu
	mainMenu.add("Addition", "(X+Y)", &arithmetic);
	mainMenu.add("Subtraction", "(X-Y)", &arithmetic);
	mainMenu.add("Multiplication", "(X*Y)", &arithmetic);
	mainMenu.add("Division", "(X/Y)", &arithmetic);
	mainMenu.add("Roots", "(Square Root, CubeRoot)", &roots);
	mainMenu.add("Powers", "(X-Squared, X-Cubed)", &powers);
	mainMenu.add("Geometry", "(Area, Perimeter)", &geometry);

	//Now sub-menus
	//Each option here takes a function pointer
	arithmetic.add("Addition", "(X+Y)", &sum);
	arithmetic.add("Subtraction", "(X-Y)", &sub);
	arithmetic.add("Multiplication", "(X*Y)", &mult);
	arithmetic.add("Division", "(X/Y)", &div);

	roots.add("Take the square root of a number", "", &sqRt);
	roots.add("Take the cube root of a number", "", &cbRt);

	powers.add("Square a number", "", &sqr);
	powers.add("Cube a number", "", &cub);

	geometry.add("Circle", "(Area and Circumference)", &circ);
	geometry.add("Rectangle", "(Area and Perimeter)", &rect);
	geometry.add("Triangle", "(Area and Perimeter)", &tri);

	//Display main menu
	//Automatically loops, so we don't have to worry about a thing
	mainMenu.display();
}

void getFromInput(double& x, char altEnter, bool doInt) {
	char button; //What the user pressed
	//We use a char array as a buffer instead of a double because it's much easier to manage printing
	//Goes to 100 digits, which is more than we can store in a double
	char buff[100]; 
	unsigned int index = 0; //Keeps track of where we are located in the buffer

	while(true) {
		button = _getch(); //Wait for user input

		unsigned int _index = index; //Store where we just were for use later, in case it changes
		switch(button) {
			case '.':
				if (doInt) break; //We won't let people type decimal points unless they chose "float" earlier
			case '0':
				if (!index) break; //We don't want people entering in '0' or '.' if there's nothing already there
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				//Pretty simple - add a number (or decimal point) onto the end
				buff[index++] = button;
				break;
			case '\b': //BACKSPACE
				//
				if(index) buff[--index] = NULL;
				break;
			case 13: //ENTER
				//Our job is done - turn our char array into a double and return;
				x = atof(buff);
				return;
		}

		//I want people to be able to press '+' for sum, '-' for range, etc. instead of being forced to press enter
		if (button == altEnter) {
			x = atof(buff);
			return;
		}

		//CLEAR LINE
		//First, we clear the number of characters that we were displaying previously
		//But this doesn't actually clear them from the console - you have to overwrite them with something
		//This would be fine if our number were growing in digits, but if you had '567' and typed backspace, '567' would still show up, even if you only printed '56'
		//So, we overwrite everything with whitespace, then back up to the beginning again.
		for (unsigned int i = 0; i < _index; i++) {
			cout << '\b';
		}
		for (unsigned int i = 0; i < _index; i++) {
			cout << ' ';
		}
		for (unsigned int i = 0; i < _index; i++) {
			cout << '\b';
		}
		//END CLEAR LINE

		//Then, print our number
		//I previously had done cout << buff instead of this loop
		//But all of the NULL indexes made it print out some weird stuff to the console
		for (unsigned int i = 0; i < index; i++) {
			cout << buff[i];
		}
		 
	}	
}

//Ask the user for variable inputs in various different manners/formatting

void getFromInput(char* beg, double& x, char* sep, double& y, bool doInt) {
	cout << beg;
	getFromInput(x, *sep, doInt);
	cout << ' ' << sep << ' ';
	getFromInput(y, '=', doInt);
}

void getFromInput(double& x, char* sep, double& y, double& z, bool doInt) {
	getFromInput(x, *sep, doInt);
	cout << ' ' << sep << ' ';
	getFromInput(y, *sep, doInt);
	cout << ' ' << sep << ' ';
	getFromInput(z, '=', doInt);
}

void getFromInput(double& x, char* sep, double& y, bool doInt) {
	getFromInput("Please input your formula: ", x, sep, y, doInt);
}

void getFromInput(char* beg, double& x, bool doInt) {
	cout << beg << '(';
	getFromInput(x, ')', doInt);
	cout << ")";
}

//ARITHMETIC FUNCTIONS

void sum(bool doInt) {
	double x, y;
	getFromInput(x, "+", y, doInt);
	cout << " = " << x + y;
}

void sub(bool doInt) {
	double x, y;
	getFromInput(x, "-", y, doInt);
	cout << " = " << x - y;
}

void mult(bool doInt) {
	double x, y;
	getFromInput(x, "*", y, doInt);
	cout << " = " << x * y;
}

void div(bool doInt) {
	double x, y;
	getFromInput(x, "/", y, doInt);
	if(doInt) cout << " = " << (int) (x / y);
	else cout << " = " << x / y;
}

//ROOT FUNCTIONS
void sqRt(bool doInt) {
	double x;
	getFromInput("Please input your formula: sqrt", x, doInt);
	if (doInt) cout << " = " << (int)sqrt(x);
	else cout << " = " << sqrt(x);
}
void cbRt(bool doInt) {
	double x;
	getFromInput("Please input your formula: cbrt", x, doInt);
	if (doInt) cout << " = " << (int)cbrt(x);
	else cout << " = " << cbrt(x);
}

//POWER FUNCTIONS
void sqr(bool doInt) {
	double x;
	getFromInput("Please input your formula: sqr", x, doInt);
	cout << " = " << pow(x, 2);
}

void cub(bool doInt) {
	double x;
	getFromInput("Please input your formula: cub", x, doInt);
	cout << " = " << pow(x, 3);
}

//GEOMETRIC FUNCTIONS
void circ(bool doInt) {
	double r;
	getFromInput("Circle radius: ", r, doInt);
	double a = pi() * pow(r, 2);
	double c = 2 * pi() * r;

	cout << "\nArea: ";
	if (doInt) cout << (int)a;
	else cout << a;

	cout << "\nCircumference: ";
	if (doInt) cout << (int)c;
	else cout << c;
}

void rect(bool doInt) {
	double h, w;
	getFromInput("Height and width of Rectangle: ", h, ",", w, doInt);
	double a = h * w;
	double p = 2 * h + 2 * w;

	cout << "\nArea: ";
	if (doInt) cout << (int)a;
	else cout << a;

	cout << "\nPerimeter: ";
	if (doInt) cout << (int)p;
	else cout << p;
}

void tri(bool doInt) {
	double a, b, c;
	cout << "Length of Triangle sides: ";
	getFromInput(a, ",", b, c, doInt);
	double p = a + b + c;
	double p2 = p / 2;
	double ar = sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));

	cout << "\nArea: ";
	if (doInt) cout << (int)ar;
	else cout << ar;

	cout << "\nPerimeter: ";
	if (doInt) cout << (int)p;
	else cout << p;
}