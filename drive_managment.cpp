#include "drive_managment.h"

std::vector<char> get_drives() {
	std::vector<char> drives_names;
	DWORD drives = GetLogicalDrives();
	for (char i = 0; i < constants::en_count; ++i) {
		if ((drives & 1) == 1)
			drives_names.push_back(i + constants::en_ascii_shift);
		drives >>= 1;
	}
	return drives_names;
}

void print_drives() {
	std::vector<char> drives_names = get_drives();
	std::cout << "Found " << drives_names.size() << " drives:";
	for (const char& drive_name : drives_names)
		std::cout << ' ' << drive_name;
	std::cout << '\n';
}

std::string drive_type_to_string(UINT drive_type) {
	switch (drive_type)
	{
	case DRIVE_UNKNOWN: return "DRIVE_UNKNOWN";
	case DRIVE_NO_ROOT_DIR: return "DRIVE_NO_ROOT_DIR";
	case DRIVE_REMOVABLE: return "DRIVE_REMOVABLE";
	case DRIVE_FIXED: return "DRIVE_FIXED";
	case DRIVE_REMOTE: return "DRIVE_REMOTE";
	case DRIVE_CDROM: return "DRIVE_CDROM";
	case DRIVE_RAMDISK: return "DRIVE_RAMDISK";
	default: return "UNINTENDED_VALUE";
	}
}

std::string file_system_flag_to_sring(DWORD flag) {
	switch (flag)
	{
	case FILE_CASE_PRESERVED_NAMES: return "FILE_CASE_PRESERVED_NAMES";
	case FILE_CASE_SENSITIVE_SEARCH: return "FILE_CASE_SENSITIVE_SEARCH";
	case FILE_DAX_VOLUME: return "FILE_DAX_VOLUME";
	case FILE_FILE_COMPRESSION: return "FILE_FILE_COMPRESSION";
	case FILE_NAMED_STREAMS: return "FILE_NAMED_STREAMS";
	case FILE_PERSISTENT_ACLS: return "FILE_PERSISTENT_ACLS";
	case FILE_READ_ONLY_VOLUME: return "FILE_READ_ONLY_VOLUME";
	case FILE_SEQUENTIAL_WRITE_ONCE: return "FILE_SEQUENTIAL_WRITE_ONCE";
	case FILE_SUPPORTS_ENCRYPTION: return "FILE_SUPPORTS_ENCRYPTION";
	case FILE_SUPPORTS_EXTENDED_ATTRIBUTES: return "FILE_SUPPORTS_EXTENDED_ATTRIBUTES";
	case FILE_SUPPORTS_HARD_LINKS: return "FILE_SUPPORTS_HARD_LINKS";
	case FILE_SUPPORTS_OBJECT_IDS: return "FILE_SUPPORTS_OBJECT_IDS";
	case FILE_SUPPORTS_OPEN_BY_FILE_ID: return "FILE_SUPPORTS_OPEN_BY_FILE_ID";
	case FILE_SUPPORTS_REPARSE_POINTS: return "FILE_SUPPORTS_REPARSE_POINTS";
	case FILE_SUPPORTS_SPARSE_FILES: return "FILE_SUPPORTS_SPARSE_FILES";
	case FILE_SUPPORTS_TRANSACTIONS: return "FILE_SUPPORTS_TRANSACTIONS";
	case FILE_SUPPORTS_USN_JOURNAL: return "FILE_SUPPORTS_USN_JOURNAL";
	case FILE_UNICODE_ON_DISK: return "FILE_UNICODE_ON_DISK";
	case FILE_VOLUME_IS_COMPRESSED: return "FILE_VOLUME_IS_COMPRESSED";
	case FILE_VOLUME_QUOTAS: return "FILE_VOLUME_QUOTAS";
	case FILE_SUPPORTS_BLOCK_REFCOUNTING: return "FILE_SUPPORTS_BLOCK_REFCOUNTING";
	default: return "UNINTENDED_VALUE";
	}
}

void print_drive_type(LPCWSTR drive_path_name) {
	UINT drive_type = GetDriveType(drive_path_name);
	std::cout << "Type of drive: " << drive_type_to_string(drive_type) << '\n';
}

void print_volume_information(LPCWSTR drive_path_name) {
	const std::set<DWORD> s_flags({
		FILE_CASE_PRESERVED_NAMES,
		FILE_CASE_SENSITIVE_SEARCH,
		FILE_DAX_VOLUME,
		FILE_FILE_COMPRESSION,
		FILE_NAMED_STREAMS,
		FILE_PERSISTENT_ACLS,
		FILE_READ_ONLY_VOLUME,
		FILE_SEQUENTIAL_WRITE_ONCE,
		FILE_SUPPORTS_ENCRYPTION,
		FILE_SUPPORTS_EXTENDED_ATTRIBUTES,
		FILE_SUPPORTS_HARD_LINKS,
		FILE_SUPPORTS_OBJECT_IDS,
		FILE_SUPPORTS_OPEN_BY_FILE_ID,
		FILE_SUPPORTS_REPARSE_POINTS,
		FILE_SUPPORTS_SPARSE_FILES,
		FILE_SUPPORTS_TRANSACTIONS,
		FILE_SUPPORTS_USN_JOURNAL,
		FILE_UNICODE_ON_DISK,
		FILE_VOLUME_IS_COMPRESSED,
		FILE_VOLUME_QUOTAS,
		FILE_SUPPORTS_BLOCK_REFCOUNTING
		});
	TCHAR volume_name[constants::buffer_size];
	TCHAR file_system_name[constants::buffer_size];
	DWORD serial_number = 0;
	DWORD max_component_length = 0;
	DWORD flags = 0;
	GetVolumeInformation(drive_path_name, volume_name, constants::buffer_size, &serial_number,
		&max_component_length, &flags, file_system_name, constants::buffer_size);
	std::wcout << "Volume name: " << volume_name << '\n'
		<< "Serial number: " << serial_number << '\n'
		<< "Max component length: " << max_component_length << '\n'
		<< "File system name: " << file_system_name << '\n'
		<< "File system flags:\n";
	for (const DWORD& flag : s_flags) {
		if (s_flags.count(flag & flags) == 1)
			std::cout << "\t* " << file_system_flag_to_sring(flag) << '\n';
	}
}

void print_disk_free_space(LPCWSTR drive_path_name) {
	DWORD sectors_per_cluster = 0;
	DWORD bytes_per_sector = 0;
	DWORD number_of_free_clusters = 0;
	DWORD total_number_of_clusters = 0;
	GetDiskFreeSpace(drive_path_name, &sectors_per_cluster, &bytes_per_sector,
		&number_of_free_clusters, &total_number_of_clusters);
	std::cout << "Sectors per cluster: " << sectors_per_cluster << '\n'
		<< "Bytes per sector: " << bytes_per_sector << '\n'
		<< "Number of free clusters: " << number_of_free_clusters << '\n'
		<< "Total number of clusters: " << total_number_of_clusters << '\n';
}