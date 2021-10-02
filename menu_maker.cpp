#include "menu_maker.h""

Menu make_mainmenu() {
	return Menu(
		"MAIN MENU",
		"Exit",
		std::vector<Item>({
			Item("Drive management", []() { menu_process(make_drivemanagmentmenu()); }),
			Item("Directory management", []() { menu_process(make_directorymanagmentmenu()); }),
			Item("File management", []() { menu_process(make_filemanagmentmenu()); })
			})
	);
}

Menu make_drivemanagmentmenu() {
	return Menu(
		"DRIVE MANAGMENT MENU",
		"Go back",
		std::vector<Item>({
			Item("Get a list of all drives", []() { print_drives(); system("pause"); }),
			Item("Get drive information", []() { menu_process(make_drivesmenu()); })
			})
	);
}

Menu make_directorymanagmentmenu() {
	return Menu(
		"DIRECTORY MANAGMENT MENU",
		"Go back",
		std::vector<Item>({
			Item("Create directory", []() { process_ñreate_directory(); system("pause"); }),
			Item("Remove directory", []() { process_remove_directory(); system("pause"); })
			})
	);
}

Menu make_filemanagmentmenu() {
	return Menu(
		"FILE MANAGMENT MENU",
		"Go back",
		std::vector<Item>({
			Item("Create file", []() { process_create_file(); system("pause"); }),
			Item("Move file", []() { process_move_file(); system("pause"); }),
			Item("Copy file", []() { process_copy_file(); system("pause"); }),
			Item("File attributes management", []() { menu_process(make_attributesmanagmentmenu()); })
			})
	);
}

Menu make_attributesmanagmentmenu() {
	return Menu(
		"FILE ATTRIBUTES MANAGMENT MENU",
		"Go back",
		std::vector<Item>({
			Item("Get attributes", []() { process_get_file_attributes(); system("pause"); }),
			Item("Get time attributes", []() { process_get_file_time(); system("pause"); }),
			Item("Get attributes by handle", []() { processFileInformation(); system("pause"); }),
			Item("Set attributes", []() { menu_process(make_attributesmenu()); }),
			Item("Set time attributes", []() { process_set_file_time(); system("pause"); })
			})
	);
}

Menu make_drivesmenu() {
	std::vector<Item> v_items;
	std::vector<char> v_drives = get_drives();
	for (const auto& drive : v_drives) {
		std::string s_drive = { drive };
		v_items.push_back(
			Item(s_drive,
				[=]() {
					const TCHAR path[constants::drive_path_size] = { drive, ':', '\\', '\0'};
					print_drive_type(path);
					print_volume_information(path);
					print_disk_free_space(path);
					system("pause");
				}
			)
		);
	}
	return Menu(
		"DRIVES MENU",
		"Go back",
		v_items
	);
}

Menu make_attributesmenu() {
	std::vector<Item> v_items;
	std::vector<DWORD> v_attribures({
		FILE_ATTRIBUTE_ARCHIVE,
		FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_NORMAL,
		FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
		FILE_ATTRIBUTE_OFFLINE,
		FILE_ATTRIBUTE_READONLY,
		FILE_ATTRIBUTE_SYSTEM,
		FILE_ATTRIBUTE_TEMPORARY
	});
	for (const auto& attribute : v_attribures) {
		v_items.push_back(
			Item(file_attribute_to_string(attribute),
				[=]() {
					process_set_file_attributes(attribute);
					system("pause");
				}
			)
		);
	}
	return Menu(
		"ATTRIBUTES MENU",
		"Go back",
		v_items
	);
}