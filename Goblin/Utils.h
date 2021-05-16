#pragma once
#include "Main.h"

std::string get_last_error_as_str();
PWSTR get_desktop_path();
std::wstring gen_filename(Filename_fmt);
std::wstring gen_num_str(int);
