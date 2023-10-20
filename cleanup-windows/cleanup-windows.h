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
				std::cerr << "[-] Failed to clean icon and thumbcache." << std::endl;
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
	};
}

MIT License

Copyright (c) 2023 REVRBE

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

#endif
