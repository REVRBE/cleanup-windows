#include "cleanup-windows.h"

//
// PROCESS UTILS
//
bool internals::process_utils::enable_privilege(const wchar_t* privilege_name)
{
    HANDLE h_token;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &h_token)) {
        TOKEN_PRIVILEGES tkp;
        if (LookupPrivilegeValue(NULL, privilege_name, &tkp.Privileges[0].Luid)) {
            tkp.PrivilegeCount = 1;
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if (AdjustTokenPrivileges(h_token, FALSE, &tkp, 0, NULL, NULL)) {
                CloseHandle(h_token);
                return true;
            }
        }
        CloseHandle(h_token);
    }
    return false;
}

void internals::process_utils::restart_explorer()
{
    // Find all explorer.exe processes and terminate them
    DWORD explorer_pid = 0;
    std::vector<DWORD> explorer_pids;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process_entry;
    process_entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &process_entry)) {
        do {
            if (_wcsicmp(process_entry.szExeFile, L"explorer.exe") == 0) {
                explorer_pids.push_back(process_entry.th32ProcessID);
            }
        } while (Process32Next(snapshot, &process_entry));
    }
    CloseHandle(snapshot);

    // Terminate all explorer.exe instances
    for (DWORD pid : explorer_pids) {
        HANDLE h_process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if (h_process != NULL) {
            TerminateProcess(h_process, 0);
            CloseHandle(h_process);
        }
    }

    // Restart explorer.exe
    ShellExecute(NULL, L"open", L"explorer.exe", NULL, NULL, SW_SHOWNORMAL);
}

//
// FILE UTILS
//
std::wstring internals::file_utils::get_user_profile_directory()
{
    TCHAR user_profile[MAX_PATH];
    if (GetEnvironmentVariable(TEXT("USERPROFILE"), user_profile, MAX_PATH) == 0) {
        std::wcerr << L"[-] Failed to retrieve user profile directory." << std::endl;
        return L"";
    }
    return user_profile;
}

void internals::file_utils::delete_files_in_folder_with_read_only(const std::wstring& folder_path)
{
    WIN32_FIND_DATA find_file_data;
    HANDLE h_find = FindFirstFile((folder_path + L"*").c_str(), &find_file_data);
    if (h_find != INVALID_HANDLE_VALUE) {
        do {
            if (wcscmp(find_file_data.cFileName, L".") != 0 && wcscmp(find_file_data.cFileName, L"..") != 0) {
                std::wstring file_path = folder_path + find_file_data.cFileName;

                // Remove the read-only attribute from the file
                if (SetFileAttributes(file_path.c_str(), FILE_ATTRIBUTE_NORMAL)) {
                    if (DeleteFile(file_path.c_str())) {
                        std::wcout << L"[+] Deleted: " << file_path << std::endl;
                    }
                    else {
                        std::wcerr << L"[-] Failed to delete: " << file_path << std::endl;
                    }
                }
                else {
                    std::wcerr << L"[-] Failed to remove read-only attribute for: " << file_path << std::endl;
                }
            }
        } while (FindNextFile(h_find, &find_file_data) != 0);
        FindClose(h_find);
    }
    else {
        std::cerr << "[-] No files found in the folder." << std::endl;
    }
}

void internals::file_utils::delete_files_in_folder(const std::wstring& folderPath)
{
    std::wstring searchPath = folderPath + L"\\*.*";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::wcerr << L"[-] Error finding files in folder: " << folderPath << std::endl;
        return;
    }

    do {
        if (wcscmp(findFileData.cFileName, L".") == 0 || wcscmp(findFileData.cFileName, L"..") == 0) {
            continue;
        }

        std::wstring filePath = folderPath + L"\\" + findFileData.cFileName;

        if (DeleteFile(filePath.c_str()) == FALSE) {
            std::wcerr << L"[-] Error deleting file: " << filePath << std::endl;
        }
        else {
            std::wcout << L"[+] Deleted: " << filePath << std::endl;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

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
