#ifndef CLEANUP_WINDOWS_H
#define CLEANUP_WINDOWS_H

#include "pch.h"

namespace internals {
	namespace process_utils {
		bool enable_privilege(const wchar_t* privilege_name);

		void restart_explorer();
	}

	namespace file_utils {
		std::wstring get_user_profile_directory();

		void delete_files_in_folder_with_read_only(const std::wstring& folder_path);

		void delete_files_in_folder(const std::wstring& folderPath);
	}

	class cleanup_windows {
	public:
		static void start_cleanup() {
			if (!internals::process_utils::enable_privilege(SE_DEBUG_NAME)) {
				std::cerr << "[-] Failed to enable debug privilege." << std::endl;
			}

			if (!clean_icon_and_thumb_cache()) {
				std::cerr << "[-] Failed to clean icon and thumbcache." << std::endl;
			}
			if (!clean_appcompat_installs()) {
				std::cerr << "[-] Failed to clean AppCompat installs." << std::endl;
			}
			if (!clean_shared_file_cache()) {
				std::cerr << "[-] Failed to clean SharedFileCache." << std::endl;
			}
			if (!clean_crashdumps()) {
				std::cerr << "[-] Failed to clean CrashDumps." << std::endl;
			}
		}

	private:
		static bool clean_icon_and_thumb_cache() {
			std::wstring explorer_path = internals::file_utils::get_user_profile_directory();
			explorer_path += L"\\AppData\\Local\\Microsoft\\Windows\\Explorer\\";

			internals::process_utils::restart_explorer();

			internals::file_utils::delete_files_in_folder_with_read_only(explorer_path);
			return true;
		}

		static bool clean_appcompat_installs() {
			std::wstring installs_path = L"C:\\Windows\\appcompat\\Programs\\Install";

			internals::file_utils::delete_files_in_folder(installs_path);
			return true;
		}

		static bool clean_shared_file_cache() {
			std::wstring cache_path = L"C:\\Windows\\SoftwareDistribution\\Download\\SharedFileCache";

			internals::file_utils::delete_files_in_folder(cache_path);
			return true;
		}

		static bool clean_crashdumps() {
			std::wstring crashdumps_path = L"C:\\Users\\antia\\AppData\\Local\\CrashDumps";

			internals::file_utils::delete_files_in_folder(crashdumps_path);
			return true;
		}
	};
}

#endif
