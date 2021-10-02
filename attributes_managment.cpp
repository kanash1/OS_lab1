#include "attributes_managment.h"

std::string file_attribute_to_string(DWORD attribute) {
	switch (attribute)
	{
	case FILE_ATTRIBUTE_ARCHIVE: return "FILE_ATTRIBUTE_ARCHIVE";
	case FILE_ATTRIBUTE_COMPRESSED: return "FILE_ATTRIBUTE_COMPRESSED";
	case FILE_ATTRIBUTE_DEVICE: return "FILE_ATTRIBUTE_DEVICE";
	case FILE_ATTRIBUTE_DIRECTORY: return "FILE_ATTRIBUTE_DIRECTORY";
	case FILE_ATTRIBUTE_ENCRYPTED: return "FILE_ATTRIBUTE_ENCRYPTED";
	case FILE_ATTRIBUTE_HIDDEN: return "FILE_ATTRIBUTE_HIDDEN";
	case FILE_ATTRIBUTE_INTEGRITY_STREAM: return "FILE_ATTRIBUTE_INTEGRITY_STREAM";
	case FILE_ATTRIBUTE_NORMAL: return "FILE_ATTRIBUTE_NORMAL";
	case FILE_ATTRIBUTE_NOT_CONTENT_INDEXED: return "FILE_ATTRIBUTE_NOT_CONTENT_INDEXED";
	case FILE_ATTRIBUTE_NO_SCRUB_DATA: return "FILE_ATTRIBUTE_NO_SCRUB_DATA";
	case FILE_ATTRIBUTE_OFFLINE: return "FILE_ATTRIBUTE_OFFLINE";
	case FILE_ATTRIBUTE_READONLY: return "FILE_ATTRIBUTE_READONLY";
	case FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS: return "FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS";
	case FILE_ATTRIBUTE_RECALL_ON_OPEN: return "FILE_ATTRIBUTE_RECALL_ON_OPEN";
	case FILE_ATTRIBUTE_REPARSE_POINT: return "FILE_ATTRIBUTE_REPARSE_POINT";
	case FILE_ATTRIBUTE_SPARSE_FILE: return "FILE_ATTRIBUTE_SPARSE_FILE";
	case FILE_ATTRIBUTE_SYSTEM: return "FILE_ATTRIBUTE_SYSTEM";
	case FILE_ATTRIBUTE_TEMPORARY: return "FILE_ATTRIBUTE_TEMPORARY";
	case FILE_ATTRIBUTE_VIRTUAL: return "FILE_ATTRIBUTE_VIRTUAL";
	default: return "UNINTENDED_VALUE";
	}
}

void print_system_time(const SYSTEMTIME& time) {
	std::cout << time.wYear << '-' << time.wMonth << '-' << time.wDay
		<< ' ' << time.wDayOfWeek << ' ' << time.wHour << ':'
		<< time.wMinute << ':' << time.wSecond << ':' << time.wMilliseconds << '\n';
}

void print_file_time(const FILETIME& f_time, const std::string& time_name) {
	SYSTEMTIME s_time;
	std::cout << time_name << ": ";
	if (FileTimeToSystemTime(&f_time, &s_time))
		print_system_time(s_time);
	else
		std::cout << "CANNOT GET TIME\n";
}

void process_get_file_time() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full path and name of the file to get time info "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	HANDLE handle = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		FILETIME fc_time, fa_time, fw_time;
		if (GetFileTime(handle, &fc_time, &fa_time, &fw_time)) {
			print_file_time(fc_time, "Creation time");
			print_file_time(fa_time, "Last access time");
			print_file_time(fw_time, "Last write time");
		}
		else
			std::cout << "Error occurred while getting time info. Error code: "
			<< GetLastError() << '\n';
		CloseHandle(handle);
	}
	else
		std::cout << "Error occurred while opening the file. Error code: "
		<< GetLastError() << '\n';
}

void print_file_attributes(DWORD file_attributes) {
	std::cout << "File attributes:\n";
	const std::set<DWORD> s_attributes({
		FILE_ATTRIBUTE_ARCHIVE,
		FILE_ATTRIBUTE_COMPRESSED,
		FILE_ATTRIBUTE_DEVICE,
		FILE_ATTRIBUTE_DIRECTORY,
		FILE_ATTRIBUTE_ENCRYPTED,
		FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_INTEGRITY_STREAM,
		FILE_ATTRIBUTE_NORMAL,
		FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
		FILE_ATTRIBUTE_NO_SCRUB_DATA,
		FILE_ATTRIBUTE_OFFLINE,
		FILE_ATTRIBUTE_READONLY,
		FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS,
		FILE_ATTRIBUTE_RECALL_ON_OPEN,
		FILE_ATTRIBUTE_REPARSE_POINT,
		FILE_ATTRIBUTE_SPARSE_FILE,
		FILE_ATTRIBUTE_SYSTEM,
		FILE_ATTRIBUTE_TEMPORARY,
		FILE_ATTRIBUTE_VIRTUAL
		});
	for (const DWORD& attribute : s_attributes) {
		if (s_attributes.count(attribute & file_attributes) == 1)
			std::cout << "\t* " << file_attribute_to_string(attribute) << '\n';
	}
}

void process_get_file_attributes() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full path and name of the file to get attributes "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	DWORD file_attributes = GetFileAttributes(path);
	if (file_attributes != INVALID_FILE_ATTRIBUTES)
		print_file_attributes(file_attributes);
	else
		std::cout << "Error occurred while openning the file. Error code: "
		<< GetLastError() << '\n';
}

void processFileInformation() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full path and name of the file to get info by handle "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	HANDLE handle = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		BY_HANDLE_FILE_INFORMATION bhfi;
		if (GetFileInformationByHandle(handle, &bhfi)) {
			print_file_attributes(bhfi.dwFileAttributes);
			std::cout << "Serial number: " << bhfi.dwVolumeSerialNumber << '\n';
			print_file_time(bhfi.ftCreationTime, "Creation time");
			print_file_time(bhfi.ftLastAccessTime, "Last access time");
			print_file_time(bhfi.ftLastWriteTime, "Last write time");
			std::cout << "File size: "
				<< (static_cast<long long>(bhfi.nFileSizeHigh) << 32)
				+ static_cast<long long>(bhfi.nFileSizeLow) << '\n';
			std::cout << "Number of links: " << bhfi.nNumberOfLinks << '\n';
			std::cout << "Unique identifier: "
				<< (static_cast<long long>(bhfi.nFileIndexHigh) << 32)
				+ static_cast<long long>(bhfi.nFileIndexLow) << '\n';
			CloseHandle(handle);
		}
		else
			std::cout << "Error occurred while getting info by handle. Error code: "
			<< GetLastError() << '\n';
	}
	else
		std::cout << "Error occurred while opening the file. Error code: "
		<< GetLastError() << '\n';
}

void process_set_file_time() {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full path and name of the file to set time info "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	HANDLE handle = CreateFile(path, GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, NULL);
	if (handle != INVALID_HANDLE_VALUE) {
		SYSTEMTIME s_time;
		GetSystemTime(&s_time);
		FILETIME fc_time, fa_time, fw_time;
		if (SystemTimeToFileTime(&s_time, &fc_time) &&
			SystemTimeToFileTime(&s_time, &fa_time) &&
			SystemTimeToFileTime(&s_time, &fw_time)) {
			if (SetFileTime(handle, &fc_time, &fa_time, &fw_time)) {
				std::cout << "New file time succesfully set\n";
				print_file_time(fc_time, "Creation time");
				print_file_time(fa_time, "Last access time");
				print_file_time(fw_time, "Last write time");
			}
			else
				std::cout << "Error occurred while setting time info. Error code: "
				<< GetLastError() << '\n';
		}
		else
			std::cout << "Error occurred while converting time info. Error code: "
			<< GetLastError() << '\n';
		CloseHandle(handle);
	}
	else
		std::cout << "Error occurred while opening the file. Error code: "
		<< GetLastError() << '\n';
}

void process_set_file_attributes(DWORD attribute) {
	TCHAR path[constants::buffer_size];
	std::cout << "Enter the full path and name of the file to set time info "
		<< "(or press enter without input to abort process):\n";
	std::wcin.getline(path, constants::buffer_size);
	if (path[0] == 0)
		return;
	if (SetFileAttributes(path, attribute))
		std::cout << "New attribute succesfully set\n";
	else
		std::cout << "Error occurred while setting attribute. Error code: "
		<< GetLastError() << '\n';
}