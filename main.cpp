#include "Sim.h"

// Flow goes like this:
// main -> Sim (Singleton) -> World -> GameObjects

int main()
{
	Sim sim;
	sim.run();

	return 0;
}