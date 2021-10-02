#pragma once

#ifndef DRIVE_MANAGMENT_H
#define DRIVE_MANAGMENT_H

#include <windows.h>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "constants.h"

std::vector<char> get_drives();
void print_drives();
std::string drive_type_to_string(UINT);
std::string file_system_flag_to_sring(DWORD);
void print_drive_type(LPCWSTR);
void print_volume_information(LPCWSTR);
void print_disk_free_space(LPCWSTR);

#endif // !DIRECTORY_MANAGMENT_H