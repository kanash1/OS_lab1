#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include "FileAttributesManagment.h"
#include "Menu.h"

class AttributesMenu : public Menu {
public:
	AttributesMenu() : 
		file_attribures({
			FILE_ATTRIBUTE_ARCHIVE,
			FILE_ATTRIBUTE_HIDDEN,
			FILE_ATTRIBUTE_NORMAL,
			FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
			FILE_ATTRIBUTE_OFFLINE,
			FILE_ATTRIBUTE_READONLY,
			FILE_ATTRIBUTE_SYSTEM,
			FILE_ATTRIBUTE_TEMPORARY
		}) {}

	void display(const std::string& message = "") const {
		std::cout << "ATTRIBUTES MENU\n";
		for (size_t i = 0; i < file_attribures.size(); ++i)
			std::cout << i + 1 << ". " << fileAttributeToString(file_attribures[i]) << '\n';
		std::cout << "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		if (request_number == 0)
			is_exit = true;
		else if (request_number > 0 && request_number <= file_attribures.size()) {
			std::cout << "\n\n";
			processSetFileAttributes(file_attribures[request_number - 1]);
			system("pause");
		}
		else
			throw std::invalid_argument("LAST MESSAGE: There is no option with this number\n\n");
		return is_exit;
	}
private:
	std::vector<DWORD> file_attribures;
};

class FileAttributesManagementMenu : public Menu {
	void display(const std::string& message = "") const {
		std::cout << "FILE ATTRIBUTES MANAGMENT MENU\n"
			<< "1. Get attributes\n"
			<< "2. Get time attributes\n"
			<< "3. Get attributes by handle\n"
			<< "4. Set attributes\n"
			<< "5. Set time attributes\n"
			<< "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		switch (request_number) {
		case 1: {
			std::cout << "\n\n";
			processGetFileAttributes();
			system("pause");
			break;
		}
		case 2: {
			std::cout << "\n\n";
			processGetFileTime();
			system("pause");
			break;
		}
		case 3: {
			std::cout << "\n\n";
			processFileInformation();
			system("pause");
			break;
		}
		case 4: {
			menuProcessor(AttributesMenu());
			break;
		}
		case 5: {
			std::cout << "\n\n";
			processSetFileTime();
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