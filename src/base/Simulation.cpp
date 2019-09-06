#include "Pso.hpp"

template <std::size_t N>
class Simulation
{
	public:
	std::string name;
	Pso<N> *optimization;
	TestFunction<N> *tf;
	std::size_t particleQuantity;
/*
 * this function performs optimization algorithm. \
 * But in derived class one need to initialize TestFuncion. \
 * optimization initialization is optional and depends on Simulation implementation. \
 * some of derived classes have auxiliar functions that performs optimization for different optimization methods.
 * 
 */
	virtual void perform()=0;

	Simulation()=default;
};

