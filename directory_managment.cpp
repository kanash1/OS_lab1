#include "directory_managment.h"

void process_ñreate_directory() {
	std::string path;
	std::cout << "Enter the full pathname of the directory to be created "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path);
	if (path.empty())
		return;
	if (CreateDirectory(path.c_str(), nullptr))
		std::cout << "The directory at path " << path << " has been successfully created\n";
	else
		std::cout << "Error occurred while creating the directory. Error code: " << GetLastError() << '\n';
}

void process_remove_directory() {
	std::string path;
	std::cout << "Enter the full pathname of the directory to be removed "
		<< "(or press enter without input to abort process):\n";
	std::getline(std::cin, path);
	if (path.empty())
		return;
	if (RemoveDirectory(path.c_str()))
		std::cout << "The directory at path " << path << " has been successfully removed\n";
	else
		std::cout << "Error occurred while removing the directory. Error code: " << GetLastError() << '\n';
}