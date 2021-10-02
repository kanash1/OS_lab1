#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "input_helper.h"

/*void free(istream& is) {
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}*/

/*int readRequest(istream& is) {
	int request_number;
	is >> request_number;
	if (is.fail()) {
		free(is);
		throw invalid_argument("You specified an incorrect value");
	}
	return request_number;
}*/

std::string inputErrorToString(InputError input_error) {
	if (input_error == InputError::ERROR_INVALID || input_error == InputError::ERROR_TRASH) {
		return "LAST MESSAGE: Invalid value was entered\n\n";
	}
	return "";
}

int readRequest(std::istream& is) {
	int request_number;
	InputError input_error = input(is, request_number);
	if (input_error != InputError::ERROR_NORMAL) {
		throw std::invalid_argument(inputErrorToString(input_error));
	}
	return request_number;
}

class Menu {
public:
	virtual void display(const std::string& message = "") const = 0;
	virtual bool processRequest(int request_number) const = 0;
	virtual ~Menu() {};
};

void menuProcessor(const Menu& menu) {
	std::string message = "";
	bool is_exit = false;
	int request_number = 0;
	do {
		system("cls");
		menu.display(message);
		try {
			request_number = readRequest(std::cin);
			is_exit = menu.processRequest(request_number);
			message = "";
		}
		catch (std::exception ex) {
			message = ex.what();
		}
	} while (!is_exit);
}