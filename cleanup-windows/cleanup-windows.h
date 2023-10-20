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

		void delete_files_in_folder(const std::wstring& folder_path);
	}

	class cleanup_windows {
	public:
		static void start_cleanup() {
			if (!clean_icon_and_thumb_cache()) {
				std::cerr << "[-] Failed to clean icon and thumbcache." << std::endl;
			}
		}

	private:
		static bool clean_icon_and_thumb_cache() {
			if (!internals::process_utils::enable_privilege(SE_DEBUG_NAME)) {
				std::cerr << "[-] Failed to enable debug privilege." << std::endl;
			}

			std::wstring explorer_path = internals::file_utils::get_user_profile_directory();
			explorer_path += L"\\AppData\\Local\\Microsoft\\Windows\\Explorer\\";

			internals::process_utils::restart_explorer();

			internals::file_utils::delete_files_in_folder(explorer_path);
			return true;
		}
	};
}

#endif