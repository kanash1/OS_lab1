#pragma once

#include <iostream>
#include <string>
#include "Menu.h"
#include "DirectoryManagment.h"

class DirectoryManagmentMenu : public Menu {
	void display(const std::string& message = "") const {
		std::cout << "DIRECTORY MANAGMENT MENU\n"
			<< "1. Create directory\n"
			<< "2. Remove directory\n"
			<< "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		switch (request_number) {
		case 1: {
			std::cout << "\n\n";
			processCreateDirectory();
			system("pause");
			break;
		}
		case 2: {
			std::cout << "\n\n";
			processRemoveDirectory();
			system("pause");
			break;
		}
		case 0: {
			is_exit = true;
			break;
		}
		default:
			throw std::invalid_argument("LAST MESSAGE: There is no option with this number\n\n");
			break;
		}
		return is_exit;
	}
};