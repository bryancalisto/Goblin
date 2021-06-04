#pragma once
#include "Main.h"
#include<atomic>
#include<vector>

std::string get_last_error_as_str();
PWSTR get_desktop_path();
std::wstring gen_filename(Filename_fmt);
std::wstring gen_num_str(int);
void heat_cpu(std::atomic_bool &);
std::vector<std::wstring> get_goblin_files_from_path(PWSTR);
void startCMD();
