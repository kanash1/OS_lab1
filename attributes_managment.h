#pragma once

#ifndef ATTRIBUTES_MANAGMENT_H
#define ATTRIBUTES_MANAGMENT_H

#include <windows.h>
#include <string>
#include <iostream>
#include <set>
#include "constants.h"

std::string file_attribute_to_string(DWORD);
void print_system_time(const SYSTEMTIME&);
void print_file_time(const FILETIME&, const std::string&);
void process_get_file_time();
void print_file_attributes(DWORD);
void process_get_file_attributes();
void processFileInformation();
void process_set_file_time();
void process_set_file_attributes(DWORD);

#endif // !ATTRIBUTES_MANAGMENT_H