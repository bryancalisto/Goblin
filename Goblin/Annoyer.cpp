#include "Annoyer.h"
#include "Main.h"

Annoyer::Annoyer()
{
	time_t now = time(NULL);
	localtime_s(&born_date, &now);
}

//TODO: Add jokes functions implementations
int Annoyer::j_cli_with_msg(char* msg) {
	return -1;
}

int Annoyer::j_desktop_shuffle() {
	return -1;
}

int Annoyer::j_time_date_mod(tm* time, bool mod_date) {
	return -1;
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

