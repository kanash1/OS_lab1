#include "directory_managment.h"

void process_ñreate_directory() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full pathname of the directory to be created "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	if (CreateDirectory(path, nullptr))
		std::cout << "The directory at path " << path << " has been successfully created\n";
	else
		std::cout << "Error occurred while creating the directory. Error code: " << GetLastError() << '\n';
}

void process_remove_directory() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full pathname of the directory to be removed "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	if (RemoveDirectory(path))
		std::cout << "The directory at path " << path << " has been successfully removed\n";
	else
		std::cout << "Error occurred while removing the directory. Error code: " << GetLastError() << '\n';
}