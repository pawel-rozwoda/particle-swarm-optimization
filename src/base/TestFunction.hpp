#include "Cartesian.cpp" 

template <std::size_t N>
class TestFunction
{
	public:
	virtual double getValue(Cartesian<N> & c)=0;
	virtual Cartesian<N> & getGradient(Cartesian<N> & c)=0; 
	virtual Cartesian<N> & expectedResult()=0;
	virtual double expectedValue()=0;
};


