#include "Main.h"
#include "Utils.h"
#include <windows.h>
#include <shlobj.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <limits.h>
#include <vector>
#include <regex>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string get_last_error_as_str()
{
	// Get the error message ID, if any
	DWORD error_message_id = ::GetLastError();
	if (error_message_id == 0) {
		return std::string(); // No error message has been recorded
	}

	LPSTR message_buffer = nullptr;

	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error_message_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, NULL);

	std::string message(message_buffer, size);
	LocalFree(message_buffer);
	return message;
}

PWSTR get_desktop_path()
{
	PWSTR path = NULL;
	HRESULT res = SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &path);

	if (res != S_OK) {
		CoTaskMemFree(path);
		return NULL;
	}

	// Don't forget to free 'path' memory in the calling process
	return path;
}

std::wstring gen_num_str(int len) {
	std::wstring str;

	str.reserve(len);

	str = NUMS[rand() % 10];
	for (int i = 1; i < len; i++) {
		str += NUMS[rand() % 10];
	}

	return str;
}

std::wstring gen_eastern_str(int len) {
	std::wstring str;
	size_t n_letters = std::end(EASTERN_LETTERS) - std::begin(EASTERN_LETTERS);

	str.reserve(len);
	str = EASTERN_LETTERS[rand() % n_letters];

	for (int i = 1; i < len; i++) {
		str += EASTERN_LETTERS[rand() % n_letters];
	}

	return str;
}

// Generates filenames according to the specified format
std::wstring gen_filename(Filename_fmt fn_fmt) {
	switch (fn_fmt)
	{
	case Filename_fmt::eastern:
		return gen_eastern_str(5) + L"$&#";
	case Filename_fmt::name_num:
		return gen_num_str(4) + L"_" + NAMES[rand() % 20] + L"$&#";
		break;
	case Filename_fmt::only_num:
		return gen_num_str(5) + L"$&#";
		break;
	default:
		break;
	}

	return NULL;
}

void heat_cpu(std::atomic_bool& stop_flag) {
	double* a, * b, * c, * d;
	double e, f, g, h;
	int i = 0, j = 0;

	a = &e;
	b = &f;
	c = &g;
	d = &h;

	// Do some trivial business until killed
	while (!stop_flag) {
		*a += 1.144564542315345;
		*b += 1.144564542315345;
		*c += 1.144564542315345;
		*d += 1.144564542315345;
		i++;
		j++;

		if (*a == DBL_MAX) {
			*a = 0;
		}
		if (*b == DBL_MAX) {
			*b = 0;
		}
		if (*c == DBL_MAX) {
			*c = 0;
		}
		if (*d == DBL_MAX) {
			*d = 0;
		}
		if (i == INT_MAX) {
			i = 0;
		}
		if (j == INT_MAX) {
			j = 0;
		}
	}
}

// Gets the list of files that were created by Goblin
std::vector<std::wstring> get_goblin_files_from_path(PWSTR path) {
	std::wregex rgx(L"\\$&#");
	std::vector<std::wstring> files;
	std::wstring tmp;

	for (const auto& entry : fs::directory_iterator(path)) {
		tmp = entry.path();

		if (std::regex_search(tmp, rgx)) {
			files.push_back(entry.path());
		}
	}

	return files;
}


void startCMD() {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	wchar_t cmd_exe[500];
	wchar_t args[50] = L"/k echo hi && ping 127.0.0.1 -n 6 > nul && exit";

	ZeroMemory(&si, sizeof(STARTUPINFOW));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(si);

	GetEnvironmentVariable(L"COMSPEC", cmd_exe, 500);

	if (CreateProcessW(cmd_exe, args, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
		DWORD dwExitCode = 0;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		CloseHandle(pi.hProcess);
	}
}

int restoreShuffledDesktop() {
	TCHAR win_path[MAX_PATH];
	PWSTR desktop_path;
	std::ifstream testFile;
	std::wstringstream ss;
	// Must get the handle of desktop's listview and then you can reorder that listview
	HWND progman = FindWindow(L"progman", NULL);
	HWND shell = FindWindowEx(progman, NULL, L"shelldll_defview", NULL);
	HWND hwndListView = FindWindowEx(shell, NULL, L"syslistview32", NULL);
	int nIcons = ListView_GetItemCount(hwndListView);

	// Create rollback data file in C:\windows if it does not exist
	//GetWindowsDirectory(win_path, MAX_PATH);
	desktop_path =  get_desktop_path();

	//ss << win_path << L"\\tools_189702.sys";
	ss << desktop_path << L"\\tools_189702.sys";

	testFile.open(ss.str().c_str(),  std::ios::binary);

	if (testFile) {
		POINT* original_positions = new POINT[500]; // Defined 500 icons as max
		int index = 0;
		while (testFile.read(reinterpret_cast<char*>(&original_positions[index]), sizeof(POINT))) {
			ListView_SetItemPosition(hwndListView, index, original_positions[index].x, original_positions[index].y);
			index++;
		}
		delete[] original_positions;
		testFile.close();
	}
	else {
		return -1;
	}

	return 0;
}
