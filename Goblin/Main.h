#pragma once
#include <ctime>
#include <iostream>
#include <windows.h>

/*The list of jokes that the Goblin can make to users*/
enum class Jokes
{
	dont,
	cli_with_msg,
	desktop_shuffle,
	time_date_mod,
	files_creation,
	files_removal,
	cpu_burn,
	ram_fill,
	turn_on_off_fans
};

/*Data structure to pass data to jokes functions*/
typedef struct joke_data {
	char* str_1;
	char* str_2;
	tm *date_1;
	tm *date_2;
	bool bool_1;
	bool bool_2;
	int int_1;
	int int_2;
} joke_data;
