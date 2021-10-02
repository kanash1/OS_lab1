#pragma once

#ifndef MENU_MAKER_H
#define MENU_MAKER_H

#include "menu.h"
#include "drive_managment.h"
#include "directory_managment.h"
#include "file_managment.h"
#include "attributes_managment.h"
#include "constants.h"

Menu make_mainmenu();
Menu make_drivemanagmentmenu();
Menu make_drivesmenu();
Menu make_directorymanagmentmenu();
Menu make_filemanagmentmenu();
Menu make_attributesmanagmentmenu();
Menu make_attributesmenu();

#endif // !MENU_MAKER_H