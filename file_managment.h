#pragma once

#ifndef FILE_MANAGMENT_H
#define FILE_MANAGMENT_H

#include <iostream>
#include <windows.h>

#undef max

#include "input_helper.h"
#include "constants.h"

void process_create_file();
void process_move_file();
void process_copy_file();

#endif // !FILE_MANAGMENT_H