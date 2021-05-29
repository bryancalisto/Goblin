#pragma once
#include "Main.h"

/*
This is the goblin's brain part that's responsible of annoying users.
*/

class  Annoyer
{
public:
	int jokes_ok = 0;
	int jokes_error = 0;
	struct tm born_date;

	Annoyer();

	int joke(Jokes j, joke_data *j_data) {
		int res;

		switch (j)
		{
		case Jokes::cli_with_msg:
			res = j_cli_with_msg(j_data->str_1);
			break;
		case Jokes::desktop_shuffle:
			res = j_desktop_shuffle();
			break;
		case Jokes::time_date_mod:
			res = j_time_date_mod(j_data->date_1, j_data->bool_1);
			break;
		case Jokes::files_creation:
			res = j_files_creation(j_data->int_1, j_data->fn_fmt);
			break;
		case Jokes::files_removal:
			res = j_files_removal();
			break;
		case Jokes::cpu_burn:
			res = j_cpu_burn(j_data->int_1);
			break;
		case Jokes::dont:
		default:
			res = 0;
			break;
		}

		if (res == 0) {
			jokes_ok++;
		}
		else {
			jokes_error++;
		}

		return res;
	}

	/*Note: The 'j' prefix stands for 'joke'*/

	/*Show a cli with some funny message*/
	int j_cli_with_msg(char *msg);

	/*Reposition the desktop icons*/
	int j_desktop_shuffle();

	/*Modify just the time, not date, of the computer*/
	int j_time_date_mod(tm *time, bool mod_date);

	/*
	Populate desktop with dummy files. 
	*/
	int j_files_creation(int max_files, Filename_fmt fn_fmt);

	/*
	Delete the previously created dummy files.
	This could come in handy when has been detected that the user is removing
	the dummy files; then, when know we have her attention, so remove the files,
	or maybe create/remove new files for a moment?
	*/
	int j_files_removal();

	/*
	Heat the CPU by doing some expensive computation
	Fork a children process and run an infinite loop or benchmark test
	within it during some time.
	*/
	int j_cpu_burn(int seconds);
};
