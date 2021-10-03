#include "file_managment.h"

void process_create_file() {
	std::string path;
	std::cout << "Enter the full path and name of the file to be created "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path);
	if (path.empty())
		return;
	HANDLE handle = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		std::cout << "The file was created successfully\n";
		CloseHandle(handle);
	}
	else
		std::cout << "Error occurred while creating the file. Error code: " << GetLastError() << '\n';
}

void process_move_file() {
	std::string path1;
	std::cout << "Enter the full path and name of the file to be moved "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path1);
	if (path1.empty())
		return;
	std::string path2;
	std::cout << "Enter the full path and name of the file to be created "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path2);
	if (path2.empty())
		return;
	if (MoveFile(path1.c_str(), path2.c_str()))
		std::cout << "The file was moved successfully\n";
	else {
		DWORD error_code = GetLastError();
		if (error_code == ERROR_FILE_EXISTS || error_code == ERROR_ALREADY_EXISTS) {
			char choice;
			std::cout << "The file already exists. Overwrite? Y - yes, N - no: ";
			InputError input_error = input(std::cin, choice);
			if (input_error == InputError::ERROR_NORMAL) {
				if (choice == 'Y') {
					if (MoveFileEx(path1.c_str(), path2.c_str(), MOVEFILE_REPLACE_EXISTING))
						std::cout << "The file was moved successfully\n";
					else
						std::cout << "Error occurred while moving the file. Error code: "
						<< GetLastError() << '\n';
				}
				else if (choice == 'N')
					std::cout << "The file was not moved\n";
				else
					std::cout << "Invalid value was entered. Request execution stopped\n";
			}
			else if (input_error == InputError::ERROR_NEL)
				std::cout << "Nothing was entered. Request execution stopped\n";
			else
				std::cout << "Invalid value was entered. Request execution stopped\n";
		}
		else
			std::cout << "Error occurred while moving the file. Error code: "
			<< GetLastError() << '\n';
	}
}

void process_copy_file() {
	std::string path1;
	std::cout << "Enter the full path and name of the file to be copied "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path1);
	if (path1.empty())
		return;
	std::string path2;
	std::cout << "Enter the full path and name of the file to be created "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path2);
	if (path2.empty())
		return;
	if (CopyFile(path1.c_str(), path2.c_str(), true))
		std::cout << "The file was copied successfully\n";
	else {
		DWORD error_code = GetLastError();
		if (error_code == ERROR_FILE_EXISTS || error_code == ERROR_ALREADY_EXISTS) {
			char choice;
			std::cout << "The file already exists. Overwrite? Y - yes, N - no: ";
			InputError input_error = input(std::cin, choice);
			if (input_error == InputError::ERROR_NORMAL) {
				if (choice == 'Y') {
					if (CopyFile(path1.c_str(), path2.c_str(), false))
						std::cout << "The file was copied successfully\n";
					else
						std::cout << "Error occurred while coping the file. Error code: "
						<< GetLastError() << '\n';
				}
				else if (choice == 'N')
					std::cout << "The file was not copied\n";
				else
					std::cout << "Invalid value was entered. Request execution stopped\n";
			}
			else if (input_error == InputError::ERROR_NEL)
				std::cout << "Nothing was entered. Request execution stopped\n";
			else
				std::cout << "Invalid value was entered. Request execution stopped\n";
		}
		else
			std::cout << "Error occurred while coping the file. Error code: "
			<< GetLastError() << '\n';
	}
}