#pragma once

#include <iostream>
#include <string>
#include "Menu.h"
#include "FileAttributesManagementMenu.h"
#include "FileManagment.h"

class FileManagementMenu : public Menu {
	void display(const std::string& message = "") const {
		std::cout << "FILE MANAGMENT MENU\n"
			<< "1. Create file\n"
			<< "2. Move file\n"
			<< "3. Copy file\n"
			<< "4. File attributes management\n"
			<< "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		switch (request_number) {
		case 1: {
			std::cout << "\n\n";
			processCreateFile();
			system("pause");
			break;
		}
		case 2: {
			std::cout << "\n\n";
			processMoveFile();
			system("pause");
			break;
		}
		case 3: {
			std::cout << "\n\n";
			processCopyFile();
			system("pause");
			break;
		}
		case 4: {
			menuProcessor(FileAttributesManagementMenu());
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