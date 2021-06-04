#include "Main.h"
#include "Annoyer.h"

int main()
{
	Annoyer* annoyer = new Annoyer();
	joke_data j_data;
	//tm time_struct;

	// Set random generator
	srand((unsigned int)time(NULL));

	// THE FIRST JOKE ... CHANGE DATE
	//j_data.date_1 = &time_struct;
	//j_data.date_1->tm_year = 2022;
	//j_data.date_1->tm_mon = 11;
	//j_data.date_1->tm_mday = 28;
	//j_data.date_1->tm_hour = 3;
	//j_data.date_1->tm_min = 15;
	//j_data.date_1->tm_sec = 0;
	//j_data.date_1->tm_min = 0;
	//j_data.bool_1 = false;
	//annoyer->joke(Jokes::time_date_mod, &j_data);

	// SECOND ... CREATE FILES
	//j_data.int_1 = 2;
	//j_data.fn_fmt = Filename_fmt::eastern;
	//annoyer->joke(Jokes::files_creation, &j_data);

	// THIRD ... HEAT THE CPU
	//j_data.int_1 = 60; // 60 seconds
	//annoyer->joke(Jokes::cpu_burn, &j_data);

	// FOURTH ... REMOVE CREATED FILES
	//annoyer->joke(Jokes::files_removal, &j_data);

	// FIFTH ... OPEN CMD
	annoyer->joke(Jokes::cli_with_msg, &j_data);
}
