#include "Utils.h"

std::string GetLastErrorAsString()
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
