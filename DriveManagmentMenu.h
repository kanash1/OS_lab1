#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include "Menu.h"
#include "DriveManagment.h"

class DrivesMenu : public Menu {
public:
	DrivesMenu(const std::vector<char>& _drives_names) : drives_names(_drives_names) { }

	void display(const std::string& message = "") const {
		std::cout << "DRIVES MENU\n";
		for (size_t i = 0; i < drives_names.size(); ++i)
			std::cout << i + 1 << ". " << drives_names[i] << '\n';
		std::cout << "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		if (request_number == 0)
			is_exit = true;
		else if (request_number > 0 && request_number <= drives_names.size()) {
			std::cout << "\n\n";
			TCHAR drive_path_name[BUFFER_SIZE] = { drives_names[request_number - 1], ':', '\\' };
			printDriveType(drive_path_name);
			printVolumeInformation(drive_path_name);
			printDiskFreeSpace(drive_path_name);
			system("pause");
		}
		else
			throw std::invalid_argument("LAST MESSAGE: There is no option with this number\n\n");
		return is_exit;
	}
private:
	std::vector<char> drives_names;
};

class DriveManagmentMenu : public Menu {
public:
	void display(const std::string& message = "") const {
		std::cout << "DRIVE MANAGMENT MENU\n"
			<< "1. Get a list of all drives\n"
			<< "2. Get drive information\n"
			<< "0. Go back\n\n"
			<< message
			<< "Select option: ";
	}

	bool processRequest(int request_number) const {
		bool is_exit = false;
		switch (request_number) {
		case 1: {
			std::cout << "\n\n";
			printDrives();
			system("pause");
			break;
		}
		case 2: {
			menuProcessor(DrivesMenu(getDrives()));
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