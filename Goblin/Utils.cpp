#include "Main.h"
#include "Utils.h"
#include <windows.h>
#include <shlobj.h>
#include<thread>
#include<mutex>
#include<atomic>


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
		return gen_eastern_str(5);
	case Filename_fmt::name_num:
		return gen_num_str(4) + L"_" + NAMES[rand() % 20];
		break;
	case Filename_fmt::only_num:
		return gen_num_str(5);
		break;
	default:
		break;
	}

	return NULL;
}

// To heat up the CPU
void heat_cpu(std::atomic_bool &stop_flag) {
	int a = 0, b = 0, c = 0, i;

	// Do some trivial business until killed
	while (!stop_flag) {
		a++;
		b++;
		c++;
		if (a == MAXINT) {
			a = 0;
		}
		if (b == MAXINT) {
			b = 0;
		}
		if (c == MAXINT) {
			c = 0;
		}

		std::cout << a << std::endl;
	}
}

