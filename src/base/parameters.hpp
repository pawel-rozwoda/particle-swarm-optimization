#include <iostream>
#include <cmath>

namespace stochasticParameters
{
	double suppression = 0.9375;
	double aValue = 3.8;
	double bValue = 3.8125;
	double timeStep = pow(2,-12);
	double gamma = (1.-suppression)/timeStep;

	bool versatileOutput = false; 
} 

namespace sqdParameters
{
	std::size_t lowerBorder = 20;
	std::size_t upperBorder=80;
	std::size_t step = 1;
	std::size_t performanceQuantity = 10;
	double distance = 3;
}
