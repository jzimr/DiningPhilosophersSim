#include "Sim.h"
#include <stdexcept>
#include <iostream>

// Flow goes like this:
// main -> Sim (Singleton) -> World -> GameObjects

int main()
{
	try
	{
		Sim sim;
		sim.run();
	}
	catch (std::exception &e)
	{
		std::cout << "\nEXCEPTION OCCURED: " << e.what() << '\n';
	}

	return 0;
}