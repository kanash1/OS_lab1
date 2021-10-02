#pragma once

#include <iostream>
#include <string>
#include "Menu.h"
#include "DriveManagmentMenu.h"
#include "DirectoryManagmentMenu.h"
#include "FileManagementMenu.h"

class MainMenu : public Menu {
public:
	void display(const std::string& message = "") const {
		std::cout << "MAIN MENU\n"
			<< "1. Drive management\n"
			<< "2. Directory management\n"
			<< "3. File management\n"
			<< "0. Exit\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		switch (request_number) {
		case 1: {
			menuProcessor(DriveManagmentMenu());
			break;
		}
		case 2: {
			menuProcessor(DirectoryManagmentMenu());
			break;
		}
		case 3: {
			menuProcessor(FileManagementMenu());
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