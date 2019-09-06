#ifndef MAIN_
#define MAIN
#include "simulations.hpp"
#include <math.h>

/*
 *
 * usage example
 */
int main()
{
	//Drawings2d<2> h(20); //by constructor argument one could choose particle quantity of the swarm.
	//TimeConsumption<2> h(20);
	StepQuantityDependency<2> h(20);
	
	h.perform(); 
}
#endif
