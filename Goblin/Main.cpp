#include "Main.h"
#include "Annoyer.h"
#include "Utils.h"

int main()
{
	// Set random generator
	srand((unsigned int)time(NULL));
	Annoyer* annoyer = new Annoyer();
	annoyer->start_annoying();
}
