#pragma once
#include "Main.h"
#include<atomic>

std::string get_last_error_as_str();
PWSTR get_desktop_path();
std::wstring gen_filename(Filename_fmt);
std::wstring gen_num_str(int);
void heat_cpu(std::atomic_bool &);
